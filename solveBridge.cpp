#pragma once
#include "Chain.h"
#include <cmath>
#define G 0.0005
#define MAX_FORCE 0.1

Chain left_piece;
Chain right_piece;

double lp_momentum;
double rp_momentum;

//Chain должна облажать 1)Chain -- массив балок
//у каждой балки должен быть вектор соединяющий начало и конец балки в правом ортонормированном базисе с иксом напрвленным как на картинке
//cargo имеет свойство body.current_balk текущая балка на которой находится тело от нуля до n-1
//cargo имеет массу cargo.mass
//у Chain есть свойство динамическое длины и есть метод setlen и getlen. Setlen буквально аллоцирует память
//у Chain есть метод clear() который очищает массив цепочек
//у Chain есть свойство double inertial_momentum 

sf::Vector3f vector_mul (sf::Vector3f left, sf::Vector3f right)
{
    return (sf::Vector3f(left.y*right.z - left.z*right.y, -(left.x*right.z - left.z*right.x), left.x*right.y - left.y*right.x));
}

double find_module(sf::Vector3f a)
{
    return sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
}


double find_square_module(sf::Vector3f a)
{
    return (a.x*a.x + a.y*a.y + a.z*a.z);
}

double find_inertial_momentum(Chain a)
{
    double momentum = 0;
    sf::Vector3f l_sum = sf::Vector3f(0, 0, 0);
    for (int i = 0; i < a.length; i++)
    {
        if (i == 0)
        {
            momentum += a[i].mass * find_square_module(a[i].len_vecotor) /3;
            l_sum += a[i].len_vector/2;
        }
        else
        {
            l_sum += a[i-1].len_vector/2 + a[i].len_vector/2;
            momentum += a[i].mass * (find_square_module(l_sum)) + a[i].mass*find_square_module(a[i].len_vector)/12; //теорема Гюйгенса Штейнера
        }
    }
    return momentum;
}

void createSolidChains(Chain bridge, int broken_node) //broken_node [0...n], bridge[0...n-1] bridge_len [0...n]
{
    left_piece.clear();
    right_piece.clear();

    if (broken_node == 0)
    {
        left_piece.set_length(0);
        right_piece.set_length(bridge.length);
        for (int i = 0; i < bridge.length; i++)
        {
            right_piece[i] = bridge[bridge.length - 1 - i];
        }
    }
    else if (broken_node == bridge.length)
    {
        right_piece.set_length(0);
        left_piece.set_length(bridge.length);
        for (int i = 0; i < bridge.length; i++)
        {
            left_piece[i] = bridge[i];
        }
    }
    else
    {   
        left_piece.set_length(broken_node);
        right_piece.set_length(bridge.length - broken_node);
        int k;
        for (k = 0; k < broken_node; k++)
        {
            left_piece[k] = bridge[k];
        }
        int j = 0;
        for (int i = bridge.length -1; i >= k; i--)
        {
            right_piece[j] = bridge[i];
            j++;
        }
    }
    left_piece.inertial_momentum = find_inertial_momentum(left_Chain);
    right_piece.inertial_momentum = find_inertial_momentum(right_Chain);
}


void solveBridge(Chain bridge, cargo body, double dt)
{
    if (body.isFinished)
    {
        return;
    }
    if (bridge.is_broken)
    {
        //render two solid Chains
    }
    else
    {   
        std::vector<sf::Vector3f> reactions; // n+1 векторов рекции опоры в правом ортонормированном базисе, где n -- количество балок в мосте

        sf::Vector3f gravity_vector = sf::Vector3f(0, -1, 0);
        //посчитаем момент всех сил относительно начала моста:
        sf::Vector3f l_sum = sf::Vector3f(0, 0, 0); // создали вектор который в конечном счете будет хранить вектор соединящий начало и конец моста, также он будет являться расстоянием от начала моста до iой балки
        sf::Vector3f moment_sum1 = sf::Vector3f(0, 0, 0); //результирующий момент сил относительно начала моста
        int i;
        for (i = 0; i < bridge.length; i++)    // 0..n-1
        {
            if (i == 0)
            {
                l_sum += bridge[i].len_vector / 2;
            }
            else
            {
                l_sum += (bridge[i - 1].len_vector / 2) + (bridge[i].len_vector / 2);
            }
            moment_sum1 += (vector_mul(l_sum, gravity_vector))*bridge[i].mass; //момент силы тяжести относительно начала моста для i балки
        }
        l_sum +=  (bridge[i].len_vector / 2); // вектор, соединяющий начало и конец моста

        sf::Vector3f cargo_vector = sf::Vector3f(0, 0, 0); //вектор, соединяющий начало моста и груз
        for(i = 0; i < body.current_balk; i++) //body.current_balk \in [0, n];
        {
            cargo_vector += bridge[i].len_vector;
        }
        sf::Vector3f current_balk_len_vector = bridge[body.current_balk].len_vector;
        cargo_vector += (current_balk_len_vector * body.position)/bridge[body.current_balk].length; // в данной строчке нормируется вектор балки на котором находится груз и пропорционально вычисляется вектор до груза

        sf::Vector3f cargo_moment1 = vector_mul(cargo_vector, gravity_vector)*body.mass; // момент силы тяжести груза относительно начала моста
        
        moment_sum1 += cargo_moment1; // теперь данный вектор в теории равен моменту силы реакции последнего крепежа относительно начала моста, помноженного на минус единицу

        float N_end_y = moment_sum1.z/(-1*l_sum.x); //Игрек координата силы реакции последнего крепежа; здесь учитывается,что вектор соединяющий начало и конец моста имеет координаты (l_sum.x, 0, 0),
                                                   //поскольку точки крепления находятся на одном уровне.
        float total_mass = 0;
        for (i = 0; i < bridge.length; i++)
        {
            total_mass += bridge[i].mass;
        }
        float N_begin_y =-1*total_mass*G -N_end_y; //Игрек координата силы реакции самого первого крепежа; по второму закону Ньютона в проекции на ось y, N_end_y + N_begin_y = -Mg, где M - сумма масс балок

        //посчитаем момент всех сил тяжести системы отсносительно второго от начала моста шарнирного крепления кроме момента груза:
        sf::Vector3f moment_sum2 = sf::Vector3f(0, 0, 0);
        sf::Vector3f temp_l_vector = sf::Vector3f(0, 0, 0); //вектор отсчитывающий расстояние до iой балки
        moment_sum2 -= vector_mul(bridge[0].len_vector/2, gravity_vector)*bridge[0].mass; // первая балка теперь слева от полюса, поэтому знак минус
        for (i = 1; i < bridge.length; i++)
        {
            if (i == 1)
            {
                temp_l_vector += bridge[i].len_vector/2;
            }
            else
            {
                temp_l_vector += bridge[i - 1].len_vector/2 + bridge[i].len_vector/2;
            }
            moment_sum2 += vector_mul(temp_l_vector, gravity_vector)*bridge[i].mass;
        }
        //посчитаем момент силы тяжести тела относительно полюса во втором шарнирном креплении в зависимости от его расположения
        sf::Vector3f body_shoulder = sf::Vector3f(0, 0, 0);
        sf::Vector3f cargo_moment2 = sf::Vector3f(0, 0, 0);
        if (body.current_balk == 0) //груз слева от полюса
        {
            body_shoulder = (bridge[0].len_vector * body.position)/bridge[0].length - bridge[0].len_vector;
            cargo_moment2 = vector_mul(body_shoulder, gravity_vector)*body.mass;
        }
        else //груз справа от полюса
        {
            int j;
            for (j = 1; j < body.current_balk; j++)
            {
                body_shoulder += bridge[j].len_vector;
            }
            body_shoulder += (bridge[j].len_vector * body.position)/bridge[j].length;  // в данной строчке нормируется вектор балки на котором находится груз и пропорционально вычисляется вектор до груза
            cargo_moment2 = vector_mul(body_shoulder, gravity_vector)*body.mass;
        }
        moment_sum2 += cargo_moment2; // теперь в теории -1*moment_sum2 равен сумме моментов -1*vector_mul(l_1,N_1) + vector_mul((L-l_1)*N_n+1)
        sf::Vector3f l_1 = bridge[0].len_vector;
        sf::Vector3f L_l_1 = l_sum -l_1; //L_l_1 = L - l_1

        float N_begin_x = (l_1.x*N_begin_y - moment_sum2.z - L_l_1.x*N_end_y)/(l_1.y+L_l_1.y); //Икс координата силы реакции самого первого крепежа
        float N_end_x = -N_begin_x; //Икс координата силы реакции последнего крепежа по второму закону Ньютона в проекции на ось икс

        sf::Vector3f N_beg_vect = sf::Vector3f(N_begin_x, N_begin_y, 0); 
        // по второму закону Ньютона посчитаем весь массив векторов N от 0 до n
        reactions.push_back(N_beg_vect);
        for (int j = 0; j < bridge.length; j++)
        {
            if (j == 0)
            {
                if(body.current_balk != 0)
                {
                    reactions.push_back(-bridge[0].mass*gravity_vector - reactions[0]); // [N_1, N_2]
                }
                else
                {
                    reactions.push_back(-bridge[0].mass*gravity_vector - reactions[0] - body.mass*gravity_vector);
                }
            }
            else
            {
                if (body.current_balk != j)
                {
                    reactions.push_back(reactions[j] - bridge[j].mass*gravity_vector);
                }
                else
                {
                    reactions.push_back(reactions[j] - bridge[j].mass*gravity_vector - body.mass*gravity_vector);
                }
            }
        }
        for (int j = 0; j < reactions.size(); j++) //если какая-то из сил реакции больше критической то цепь рвется в крепеже
        {
            if (find_module(reactions[j]) > MAX_FORCE)
            {
                bridge.isBroken = true;
                createSolidChains(bridge, j);
                return;
            }
        }
        // обсчет поведения тела на мосту, считаем что точка движется бесконечно медленно, то есть ее импульс можно не учитывать при подсчете влияния на мост
        double pathlen = body.velocity * dt;
        while (body.posiion + pathlen > bridge[body.current_balk].length)  // путь до конца балки может быть слишком короткой и тело за dt перескакивает на следующую балку
        {
            pathlen -= bridge[body.current_balk].length - body.position;
            if (body.current_balk + 1 == bridge.length)
            {
                body.isFinished = true;                                  //тело доехало до конца моста
                return;
            }
            else
            {
                body.current_balk += 1;
                body.position = 0;
            }
        }
        body.position  = pathlen;
    }
}
