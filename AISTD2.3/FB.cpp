#include "FB.h"

void FB::set_size(size_t size) { Size = size; }
void FB::set_cities(string* cities) { towns = cities; }
void FB::set_weights(double** weights) { weights = weights; }
FB::FB()
{
	Size = 0;
	towns = nullptr;
	weights = nullptr;
}
FB::FB(string filename)
{
	set_size(0);
	fstream in(filename);
	if (!in.is_open())
		throw invalid_argument("file doesn't exist");
	Queue<size_t, string> cities;
	string city;
	while (in.peek() != EOF)
	{
		city = "";
		while (in.peek() != ';')
			city += in.get();
		if (cities.search_key(city) == -1)
			cities.push(city);
		in.get();
		city = "";
		while (in.peek() != ';')
			city += in.get();
		if (cities.search_key(city) == -1)
			cities.push(city);
		while ((in.peek() != '\n') && (in.peek() != EOF))
			in.get();
		if (in.peek() == '\n')
			in.get();
	}
	set_size(cities.get_size());
	towns = new string[get_size()];
	for (size_t i = 0; i < get_size(); i++)
		towns[i] = cities.pop()->get_data();
	weights = new double* [get_size()];
	for (size_t i = 0; i < get_size(); i++)
		weights[i] = new double[get_size()];
	for (size_t i = 0; i < get_size(); i++)
	{
		for (size_t j = 0; j < get_size(); j++)
		{
			if (i == j)
				weights[i][j] = 0;
			else
				weights[i][j] = INF;
		}
	}
	in.close();
	in.open(filename);
	while (in.peek() != EOF)
	{
		size_t index_from, index_to;
		double forward_cost, backward_cost;
		string info = "";
		while (in.peek() != ';')
			info += in.get();
		index_from = get_city_index(info);
		in.get();
		info = "";
		while (in.peek() != ';')
			info += in.get();
		index_to = get_city_index(info);
		in.get(); // read ';'
		if (in.peek() == 'N')
		{
			forward_cost = INF; // unreal cost
			while (in.get() != ';') {}
		}
		else
		{
			in >> forward_cost;
			in.get(); // read ';'
		}
		if (in.peek() == 'N')
		{
			backward_cost = INF; // unreal cost
			for (int i = 0; i < 3; i++)
				in.get(); // read "N/A"
		}
		else
			in >> backward_cost;
		if (in.peek() == '\n') // read '\n'
			in.get();
		if (forward_cost < INF)
			weights[index_from][index_to] = forward_cost;
		if (backward_cost < INF)
			weights[index_to][index_from] = backward_cost;
		// filled weights matrix
	}
}
size_t FB::get_size() { return Size; }
string* FB::get_cities() { return towns; }
double** FB::get_weights() { return weights; }

size_t FB::get_city_index(string city)
{
	for (size_t i = 0; i < get_size(); i++)
	{
		if (towns[i] == city)
			return i;
	}
	return -1; // in case of not-existing city return unreal index
}

double FB::FordBellman(string from, string to)
{
	ofstream out("output.txt");
	size_t f = get_city_index(from);
	size_t t = get_city_index(to);
	if (f == -1)
	{
		out << "the source city doesn't exist" << endl;
		throw invalid_argument("the source city doesn't exist");
	}
	if (t == -1)
	{
		out << "the target city doesn't exist" << endl;
		throw invalid_argument("the target city doesn't exist");
	}
	double min_cost = INF;
	size_t* marks = new size_t[get_size()]{ f };
	double** W = new double* [get_size()];
	for (size_t i = 0; i < get_size(); i++)
		W[i] = new double[get_size()];
	for (size_t i = 0; i < get_size(); i++)
	{
		for (size_t j = 0; j < get_size(); j++)
			W[i][j] = get_weights()[i][j];
	}
	size_t p;
	for (p = 0; p < get_size(); p++)
	{
		bool is_improoved = false;
		for (size_t node = 0; node < get_size(); node++)
		{
			for (size_t to = 0; to < get_size(); to++)
			{
				if (W[f][to] > W[f][node] + W[node][to])
				{
					W[f][to] = W[f][node] + W[node][to];
					marks[to] = node;
					is_improoved = true;
				}
			}
		}
		if (!is_improoved) // if on current phase wasn't any improvements
			break;
	}
	if (p == get_size()) // unreal, so exists a negative cycle
	{
		out << "There is a negative cycle, program stops working." << endl;
		throw invalid_argument("Found negative cycle");
	}
	min_cost = W[f][t];

	if (min_cost >= INF)
	{
		out << to << " can't be reached from " << from << endl;
		throw invalid_argument("path doesn't exist");
	}
	out << "minimum cost of reaching " << to << " from " << from << " is " << W[f][t] << endl;
	// going to restore the way and print it to the file
	size_t* reversed_way = new size_t[get_size()]{ f }; // an array saving indexes of cities in reversed order 
	size_t city = t;
	int i = 0;
	while (city != f)
	{
		reversed_way[i] = city;
		city = marks[city];
		i++;
	}
	reversed_way[i] = f;
	out << "the way:" << endl;
	for (int k = i; k >= 0; k--)
	{
		out << get_cities()[reversed_way[k]];
		if (k != 0)
			out << " -> ";
	}
	out.close();
	return W[f][t];
}