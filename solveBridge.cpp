#include "solveBridge.h"
#define EPS 1

//Chain должна облажать 1)Chain -- массив балок
//у каждой балки должен быть вектор соединяющий начало и конец балки в правом ортонормированном базисе с иксом напрвленным как на картинке
//cargo имеет свойство body.current_balk текущая балка на которой находится тело от нуля до n-1
//cargo имеет массу cargo.mass
//у Chain есть свойство динамическое длины и есть метод setlen и getlen. Setlen буквально аллоцирует память
//у Chain есть метод clear() который очищает массив цепочек
//у Chain есть свойство double inertial_momentum 

Chain left_piece;
Chain right_piece;

double lp_momentum;
double rp_momentum;

sf::Vector3f normalize_vector(sf::Vector3f v)
{
	return v/(float)find_module(v);
}

double scalar_product (sf::Vector3f a, sf::Vector3f b)
{
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

void draw_forces(Chain bridge, std::vector<sf::Vector3f> forces, std::list<Arrow>& arrows)
{
	int len = bridge.GetLen();
	float max = 0;
	int max_index;
	std::vector<float> modules;
	for (int i = 0; i < forces.size(); i++)
	{
		float temp_mod = find_module(forces[i]);
		modules.push_back(temp_mod);
		if (temp_mod > max)
		{
			max = temp_mod;
			max_index = i;
		}
	}
	int i = 0;
	for (auto& arrow : arrows)
	{
		if (i == len)
		{
		 	sf::Vector3f force_switch_basis = sf::Vector3f(forces[i].x, -forces[i].y, 0); 
  		sf::Vector3f norm_force = normalize_vector(force_switch_basis);
  		double angle = scalar_product(norm_force, sf::Vector3f(0, 1, 0));
  		arrow.initialize((bridge[i - 1].get_end()).x + 5, (bridge[i - 1].get_end()).y + 5, angle, 0);
			break;
		}
		sf::Vector2f place = bridge[i].get_begin();
		sf::Vector3f force_switch_basis = sf::Vector3f(forces[i].x, -forces[i].y, 0);
		sf::Vector3f norm_force = normalize_vector(force_switch_basis);
		double angle = scalar_product(norm_force, sf::Vector3f(0, 1, 0));
		arrow.initialize(place.x + 5, place.y + 5, angle, 1);
		i++;
	}
}

sf::Vector3f vector_mul(sf::Vector3f left, sf::Vector3f right)
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

void find_mass_center(Chain& a, int chain_type) //chain_type = 0 --> left chain, chain_type = 1 --> right_chain
{
	double  total_mass = 0;
	for (int i = 0; i < a.GetLen(); i++)
	{
		total_mass += a[i].get_mass();
	}	
	sf::Vector3f m_r = sf::Vector3f(0, 0, 0);
	for (int i = 0; i < a.GetLen(); i++)
	{
		m_r += (float)a[i].get_mass() * a[i].len_vector();
	}
	if (chain_type == 0)
	{
		a.mass_center = m_r/(float)total_mass;
	}
	else
	{
		a.mass_center = ((float)-1)*m_r/(float)total_mass;
	}
}

double find_inertial_momentum(Chain& a)
{
    double momentum = 0;
    sf::Vector3f l_sum = sf::Vector3f(0, 0, 0);
    for (int i = 0; i < a.GetLen(); i++)
    {
        if (i == 0)
        {
            momentum += a[i].get_mass() * find_square_module(a[i].len_vector()) /3;
            l_sum += a[i].len_vector()/(float)2;
        }
        else
        {
            l_sum += a[i-1].len_vector()/(float)2 + a[i].len_vector()/(float)2;
            momentum += a[i].get_mass() * (find_square_module(l_sum)) + a[i].get_mass()*find_square_module(a[i].len_vector())/12; //теорема Гюйгенса Штейнера
        }
    }
    return momentum;
}

void createSolidChains(Chain& bridge, int broken_node) //broken_node [0...n], bridge[0...n-1] bridge_len [0...n]
{
    left_piece.Clear();
    right_piece.Clear();
		left_piece.SetLen(0);	
		right_piece.SetLen(0);	
    
		if (broken_node == 0)
    {
				int len = bridge.GetLen();
        for (int i = 0; i < len; i++)
        {
						bridge[len - 1 - i];
            right_piece.add_balk(&bridge[len - 1 - i]);
        }
    }
    else if (broken_node == bridge.GetLen())
    {
				int len = bridge.GetLen();
        for (int i = 0; i < len; i++)
        {
            left_piece.add_balk(&bridge[i]);
        }
    }
    else
    {   
        int k;
        for (k = 0; k < broken_node; k++)
        {
            left_piece.add_balk(&bridge[k]);
        }
        for (int i = bridge.GetLen() -1; i >= k; i--)
        {
            right_piece.add_balk(&bridge[i]);
        }
    }
    left_piece. SetMoment(find_inertial_momentum(left_piece));
    right_piece.SetMoment(find_inertial_momentum(right_piece));
		find_mass_center(left_piece, 0);
		find_mass_center(right_piece, 1);
}


void solveBridge(Chain& bridge, Cargo& body, double dt, std::list<Arrow>& arrows)
{
    if (body.is_finished)
    {
        return;
    }
    if (bridge.get_is_broken())
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
        for (i = 0; i < bridge.GetLen(); i++)    // 0..n-1
        {
            if (i == 0)
            {
                l_sum += bridge[i].len_vector() / (float)2;
            }
            else
            {
                l_sum += (bridge[i - 1].len_vector() / (float)2) + (bridge[i].len_vector() / (float)2);
            }
            moment_sum1 += (vector_mul(l_sum, gravity_vector))*(float)bridge[i].get_mass(); //момент силы тяжести относительно начала моста для i балки
        }
        l_sum +=  (bridge[i - 1].len_vector()/(float)2); // вектор, соединяющий начало и конец моста

        sf::Vector3f cargo_vector = sf::Vector3f(0, 0, 0); //вектор, соединяющий начало моста и груз
        for(i = 0; i < body.get_current_balk(); i++) //body.current_balk \in [0, n];
        {
            cargo_vector += bridge[i].len_vector();
        }
        sf::Vector3f current_balk_len_vector = bridge[body.get_current_balk()].len_vector();
        cargo_vector += (current_balk_len_vector * (float)body.get_position())/(float)bridge[body.get_current_balk()].get_len(); // в данной строчке нормируется вектор балки на котором находится груз и пропорционально вычисляется вектор до груза

        sf::Vector3f cargo_moment1 = vector_mul(cargo_vector, gravity_vector)*(float)body.get_mass(); // момент силы тяжести груза относительно начала моста
        
        moment_sum1 += cargo_moment1; // теперь данный вектор в теории равен моменту силы реакции последнего крепежа относительно начала моста, помноженного на минус единицу

        float N_end_y = moment_sum1.z/(-1*l_sum.x); //Игрек координата силы реакции последнего крепежа; здесь учитывается,что вектор соединяющий начало и конец моста имеет координаты (l_sum.x, 0, 0),
                                                   //поскольку точки крепления находятся на одном уровне.
        float total_mass = 0;
        for (i = 0; i < bridge.GetLen(); i++)
        {
            total_mass += bridge[i].get_mass();
        }
        float N_begin_y =-1*total_mass*G -N_end_y; //Игрек координата силы реакции самого первого крепежа; по второму закону Ньютона в проекции на ось y, N_end_y + N_begin_y = -Mg, где M - сумма масс балок
				
				std::vector<float> n_y_coords;
				n_y_coords.push_back(N_begin_y);
        //вычисляю все игрек компоненты векторов N
        for (int j = 0; j < bridge.GetLen(); j++)
        {   
             if (j == 0)
             {   
                 if(body.get_current_balk() != 0)
                 {   
                     n_y_coords.push_back((float)bridge[0].get_mass()*G - n_y_coords[0]); // [N_1, N_2]
                 }
                 else
                 {   
                     n_y_coords.push_back((float)bridge[0].get_mass()*G - n_y_coords[0] + (float)body.get_mass()*G);
                 }
             }
             else
             {   
                 if (body.get_current_balk() != j)
                 {
                     n_y_coords.push_back(n_y_coords[j] + (float)bridge[j].get_mass()*G);
                 }
                 else
                 {
                     n_y_coords.push_back(n_y_coords[j] + (float)bridge[j].get_mass()*G + (float)body.get_mass()*G);
                 }
             }
         }

				bool is_found = false;
				float N_k_x;
				int index;
				//ищу первую балку под ненулевым углом чтобы применить правило моментов для нее, если такой балки нет то считается что реактивные силы по краям моста вертикальны
				for (int k = 0; k < bridge.GetLen() && !is_found; k++)
				{
					sf::Vector3f l = bridge[k].len_vector();
					if (!is_found && (l.y < -EPS || EPS < l.y))
					{
						is_found = true;
						if (body.get_current_balk() != k)
						{
							N_k_x = (l.x*G*bridge[k].get_mass()/2 + l.x*n_y_coords[k])/l.y;
						}
						else
						{
							N_k_x = (l.x * n_y_coords[k] - 0.5*l.x*bridge[k].get_mass() - ((find_module(l) - body.get_position())*l.x*G*body.get_mass())/find_module(l))/l.y;
						}
						index = k;
					}
				}
				if (!is_found)
				{
				 	N_k_x = 0;
					index = 0;
					is_found = true;
				}
        // по второму закону Ньютона посчитаем весь массив векторов N от 0 до n
				std::vector<float> n_x_coords;
				n_x_coords.resize(bridge.GetLen() + 1);
				n_x_coords[index] = N_k_x; 
				for (int k = index + 1; k < n_x_coords.size(); k++)
				{
					n_x_coords[k] = -n_x_coords[k-1];
				}
				for (int k = index - 1; k > 0; k--)
				{
					n_x_coords[k] = n_x_coords[k + 1];
				}
				for (int k = 0; k < bridge.GetLen() + 1; k++)
				{
					reactions.push_back(sf::Vector3f(n_x_coords[k], n_y_coords[k], 0));
				}
				draw_forces(bridge, reactions, arrows);
        for (int j = 0; j < reactions.size(); j++) //если какая-то из сил реакции больше критической то цепь рвется в крепеже
        {
            if (find_module(reactions[j]) > MAX_FORCE)
            {
                bridge.ch_is_broken();
                createSolidChains(bridge, j);
                return;
            }
        }
        // обсчет поведения тела на мосту, считаем что точка движется бесконечно медленно, то есть ее импульс можно не учитывать при подсчете влияния на мост
        double pathlen = body.get_speed()*dt;
				while (body.get_position() + pathlen > bridge[body.get_current_balk()].get_len())  // путь до конца балки может быть слишком короткой и тело за dt перескакивает на следующую балку
        {
            pathlen -= (bridge[body.get_current_balk()].get_len() - body.get_position());
            if (body.get_current_balk() + 1 == bridge.GetLen())
            {
                body.is_finished = true;                                  //тело доехало до конца моста
                printf("It's gone!\n");
								body.update_move(sf::Vector2f(200, 200));
								return;
            }
            else
            {
                int old_balk = body.get_current_balk();
								body.set_current_balk(old_balk + 1);
								sf::Vector3f curr_pos_vec = bridge[old_balk].len_vector()*(float)((bridge[old_balk].get_len() - body.get_position())/bridge[old_balk].get_len());
								sf::Vector2f new_coords = sf::Vector2f((body.get_sprite().getPosition()).x + curr_pos_vec.x,(body.get_sprite().getPosition()).y - curr_pos_vec.y); 
								body.update_move(new_coords);
                body.set_position(0);

            }
        }
        float old_pos = body.get_position();
				body.set_position(old_pos + pathlen);
				sf::Vector3f curr_len = bridge[body.get_current_balk()].len_vector();
				sf::Vector3f curr_pos_vec = (curr_len*(float)pathlen)/(float)find_module(curr_len);
				sf::Vector2f new_coords = sf::Vector2f((body.get_sprite().getPosition()).x + curr_pos_vec.x,(body.get_sprite().getPosition()).y - curr_pos_vec.y); 
				body.update_move(new_coords);
    }
}
