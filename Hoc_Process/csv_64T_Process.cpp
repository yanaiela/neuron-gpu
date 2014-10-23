#include "csv_64T_Process.h"
#include <boost/range/algorithm/count.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>

#include <sstream>

#include "HocHelpFunc.h"

struct ToDouble
{
	double operator()(string const &str) { return atof(str.c_str()); }
};


csv_64T_Process::csv_64T_Process()
{

}

void csv_64T_Process::Process()
{
	src.open(T64);

	if (!src.is_open())
	{
		throw runtime_error(ERR_FO + string(T64));
	}

	string line;

	// Skipping the first lines
	for (int i = 0; i < 3; i++)
	{
		getline(src, line);
	}

	bool readTopo = true;

	vector<int> apos; // apostrophe
	vector<string> type;
	vector<int> breaks;
	vector<int> dashes;

	while (line.size() > 0 && readTopo)
	{
		int aposInd = line.find(APOSTROPHE) + ONE;
		int breaksInd[2];
		breaksInd[FIRST] = line.find(BREAKS) + ONE; // first occurrence
		breaksInd[SECOND] = line.rfind(BREAKS) + ONE; // second occurrence (from the end)
		int dash = boost::count(line, DASH) - 1; // -1 for the end of the line (doesn't count)
		
		if (NOT_FOUND != breaksInd[FIRST]) // if found any |
		{
			if (NOT_FOUND == aposInd)
			{
				apos.push_back(ZERO);
				type.push_back(boost::trim_copy(line.substr(breaksInd[SECOND] + 1))); // Pushing to the end of the vector the type.
				breaks.push_back(breaksInd[SECOND]);
				dashes.push_back(dash);
			}

			else
			{
				apos.push_back(aposInd);
				type.push_back(boost::trim_copy(line.substr(breaksInd[FIRST] + 1)));
				breaks.push_back(breaksInd[FIRST]);
				dashes.push_back(dash);
			}

		}
		else
		{
			readTopo = false;
		}
		getline(src, line);

	}

	vector<int> origApos = apos; // (geresh)
	vector<int> origDashes = dashes;
	dashes.clear();
	vector<int> q = { 0 }; // check if int
	vector<int> parent = { 0 };
	vector<int> child_seg = { 0 };
	int ind = 0;
	vector<int> type_inds;
	//type_inds.resize(type.size());
	int type_ind;
	vector<string> types;
	types.resize(type.size());

	int node_break;

	if (apos.size() != ZERO)
	{
		while (q.size() != ZERO)
		{
			type_ind = q[ZERO];
			vector<int> temp = { type_ind };
			if (HocHelpFunc::Find(HocHelpFunc::VectorComparison(temp, type_inds)).size() == ZERO)
			{
				type_inds.resize(ind + ONE);
				type_inds[ind] = type_ind;
				types[ind] = type[type_ind];
				dashes.resize(ind + ONE);
				dashes[ind] = origDashes[type_ind];
				node_break = breaks[type_ind];

				if (type_ind + ONE == apos.size() || apos[type_ind] >= apos[type_ind + ONE])
				{
					ind++;
					q = HocHelpFunc::SubVector(q, ONE, q.size() - ONE);
					continue;
				}
				vector<int> end_of_tree = HocHelpFunc::Find(HocHelpFunc::VectorSmallerComparison(
					HocHelpFunc::SubVector(origApos, type_ind, origApos.size() - ONE),
					HocHelpFunc::SubVector(origApos, type_ind, type_ind)),
					1, true);

				if (end_of_tree.size() != ZERO)
				{
					for (size_t i = 0; i < end_of_tree.size(); i++)
					{
						end_of_tree[i] -= ONE;
					}
				}

				if (end_of_tree.size() == ZERO || origApos[type_ind] == ZERO)
				{
					end_of_tree.push_back(apos.size());
				}
				else
				{
					// Not sure what is here.. TODO
				}

				vector<int> childs_inds = HocHelpFunc::Find(HocHelpFunc::VectorSmallerEqualsComparison(
					HocHelpFunc::SubVector(apos, type_ind + ONE, end_of_tree[0] - ONE), // TODO not sure end_of_tree[0] is the right translate from matlab
					node_break + ONE));
				for (size_t i = 0; i < childs_inds.size(); i++)
				{
					if (ZERO == type_ind)
					{
						childs_inds[i] += (type_ind + ONE);
					}
					else
					{
						childs_inds[i] += type_ind;
					}
				}
				vector<int> zero_child = HocHelpFunc::Find(
					HocHelpFunc::VectorComparison(
					HocHelpFunc::SubVector(apos, childs_inds), ZERO));

				if (zero_child.size() != ZERO)
				{
					//hilds_inds[] TODO need to make some function that matches.
				}

				vector<int> adopted;

				for (size_t i = 0; i < childs_inds.size(); i++)
				{
					int cur_ind = childs_inds[i];
					vector<int> true_parent = HocHelpFunc::Find(HocHelpFunc::VectorSmallerComparison(
						HocHelpFunc::SubVector(apos, type_ind, cur_ind - ONE), // cur_ind - maby -2. TODO
						apos[cur_ind]));
					temp.clear();
					for (size_t j = 0; j < true_parent.size(); j++)
					{
						if (type_ind == ZERO)
						{
							temp.push_back(true_parent[j] + ONE);
						}
						else
						{
							temp.push_back(true_parent[j] + type_ind);
						}
					}
					true_parent = HocHelpFunc::Find(HocHelpFunc::VectorSmallerComparison(
						apos[cur_ind], HocHelpFunc::SubVector(breaks, temp)));

					if (HocHelpFunc::Find(HocHelpFunc::VectorSmallerComparison(ONE, true_parent)).size() != ZERO)
					{
						adopted.push_back(i);
					}
					// stopped at line 85 in matlab

				}
				if (adopted.size() != ZERO)
				{
					childs_inds.erase(childs_inds.begin() + adopted[ZERO]);
				}

				if (childs_inds.size() == ZERO && ind == ZERO)
				{
					childs_inds = HocHelpFunc::Find(HocHelpFunc::VectorComparison(apos, node_break));
				}
				vector<int> cur_seg;
				for (size_t i = 0; i < childs_inds.size(); i++)
				{
					int cur_child = childs_inds[i];
					int child_start = apos[cur_child];
					
					int parent_start;
					if (type_ind == ZERO)
					{
						parent_start = 1;
					}
					else
					{
						parent_start = apos[type_ind];
					}
					cur_seg.push_back(child_start - parent_start);
				}
				child_seg = HocHelpFunc::ConnectVectors(child_seg, HocHelpFunc::FlipLr(cur_seg));
				if (childs_inds.size() != ZERO)
				{
					q = HocHelpFunc::ConnectVectors(q, HocHelpFunc::FlipLr(childs_inds));
					parent = HocHelpFunc::ConnectVectors(parent, (HocHelpFunc::HomoVecNum(childs_inds.size(), ONE * ind + ONE))); // I don't see any reason for this line in the matlab code..
				}
				ind++;
			}

			q = HocHelpFunc::SubVector(q, 1, q.size() - ONE);
		}
	}
	else
	{
		types = type;
	}

	type = types;

	getline(src, line);
	getline(src, line);

	comp_params.resize(type.size());

	while (line.size() != ZERO)
	{
		string cur_type = boost::trim_copy(line);
		int comp_ind = GetCompIndex(type, cur_type);
		getline(src, line);
		
		// Getting the floating numbers in the line. 
		// ATTENTION!! because of the VS there is a small rounding with the numbers - so they are not exactly as they are in the 64T file.
		vector<float> dbl_vec;
		stringstream strstrm(line);
		float i;
		while (strstrm >> i)
		{
			dbl_vec.push_back(i);

			if (strstrm.peek() == C_COMMA)
				strstrm.ignore();
		}

		comp_params[comp_ind] = (dbl_vec);
		getline(src, line);
	}
	src.close();
}

int csv_64T_Process::GetCompIndex(vector<string> types, string compt_name)
{
	int counter = 0, pos = 0;
	for (size_t i = 0; i < types.size(); i++)
	{
		if (types[i].find(compt_name) != string::npos && types[i].at(compt_name.size()) == '(')
		{
			counter++;
			pos = i;
		}
	}
	return pos;
}


vector<float> csv_64T_Process::GetCompParams()
{
	vector<float> vec;
	for (size_t i = 0; i < comp_params.size(); i++)
	{
		vec.push_back(comp_params[i][ZERO]);
	}
	return vec;
}

/**
#include "csv_64T_Process.h"
#include <boost/range/algorithm/count.hpp>
#include <boost/algorithm/string.hpp>
#include "HocHelpFunc.h"


csv_64T_Process::csv_64T_Process()
{

}

void csv_64T_Process::Process()
{
	src.open(T64);

	if (!src.is_open())
	{
		throw runtime_error(ERR_FO + string(T64));
	}

	string line;

	// Skipping the first lines
	for (int i = 0; i < 3; i++)
	{
		getline(src, line);
	}

	bool readTopo = true;

	vector<int> apos; // apostrophe
	vector<string> type;
	vector<int> breaks;
	vector<int> dashes;

	while (line.size() > 0 && readTopo)
	{
		int aposInd = line.find(APOSTROPHE) + ONE;
		int breaksInd[2];
		breaksInd[FIRST] = line.find(BREAKS) + ONE; // first occurrence
		breaksInd[SECOND] = line.rfind(BREAKS) + ONE; // second occurrence (from the end)
		int dash = boost::count(line, DASH) - 1; // -1 for the end of the line (doesn't count)
		
		if (NOT_FOUND != breaksInd[FIRST]) // if found any |
		{
			if (NOT_FOUND == aposInd)
			{
				apos.push_back(ZERO);
				type.push_back(boost::trim_copy(line.substr(breaksInd[SECOND] + 1))); // Pushing to the end of the vector the type.
				breaks.push_back(breaksInd[SECOND]);
				dashes.push_back(dash);
			}

			else
			{
				apos.push_back(aposInd);
				type.push_back(boost::trim_copy(line.substr(breaksInd[FIRST] + 1)));
				breaks.push_back(breaksInd[FIRST]);
				dashes.push_back(dash);
			}

		}
		else
		{
			readTopo = false;
		}
		getline(src, line);

	}

	vector<int> origApos = apos; // (geresh)
	vector<int> origDashes = dashes;
	dashes.clear();
	vector<int> q = { 0 }; // check if int
	vector<int> parent = { 0 };
	vector<int> child_seg = { 0 };
	int ind = 1;
	vector<int> type_inds;
	//type_inds.resize(type.size());
	int type_ind;
	vector<string> types;
	types.resize(type.size());

	int node_break;

	if (apos.size() != ZERO)
	{
		while (q.size() != ZERO)
		{
			type_ind = q[ZERO];
			vector<int> temp = { type_ind };
			if (HocHelpFunc::Find(HocHelpFunc::VectorComparison(temp, type_inds)).size() == ZERO)
			{
				type_inds.resize(ind);
				type_inds[ind - ONE] = type_ind;
				types[ind - ONE] = type[type_ind - ONE];
				dashes.resize(ind);
				dashes[ind - ONE] = origDashes[type_ind - ONE];
				node_break = breaks[type_ind - ONE];

				if (type_ind == apos.size() || apos[type_ind - ONE] >= apos[type_ind])
				{
					ind++;
					q = HocHelpFunc::SubVector(q, ONE, q.size() - ONE);
					continue;
				}
				vector<int> end_of_tree = HocHelpFunc::Find(HocHelpFunc::VectorSmallerComparison(
					HocHelpFunc::SubVector(origApos, type_ind, origApos.size() - ONE),
					HocHelpFunc::SubVector(origApos, type_ind - ONE, type_ind - ONE)),
					1, true);

				if (end_of_tree.size() != ZERO)
				{
					for (size_t i = 0; i < end_of_tree.size(); i++)
					{
						end_of_tree[i] -= ONE;
					}
				}

				if (end_of_tree.size() == ZERO || origApos[type_ind - ONE] == ZERO)
				{
					end_of_tree.push_back(apos.size());
				}
				else
				{
					// Not sure what is here.. TODO
				}

				vector<int> childs_inds = HocHelpFunc::Find(HocHelpFunc::VectorSmallerEqualsComparison(
					HocHelpFunc::SubVector(apos, type_ind, end_of_tree[0] - ONE), // TODO not sure end_of_tree[0] is the right translate from matlab
					node_break + ONE));
				for (size_t i = 0; i < childs_inds.size(); i++)
				{
					childs_inds[i] += type_ind;
				}
				vector<int> zero_child = HocHelpFunc::Find(
					HocHelpFunc::VectorComparison(
					HocHelpFunc::SubVector(apos, childs_inds), ZERO));

				if (zero_child.size() != ZERO)
				{
					//hilds_inds[] TODO need to make some function that matches.
				}

				vector<int> adopted;

				for (size_t i = 0; i < childs_inds.size(); i++)
				{
					int cur_ind = childs_inds[i];
					vector<int> true_parent = HocHelpFunc::Find(HocHelpFunc::VectorSmallerComparison(
						HocHelpFunc::SubVector(apos, type_ind - ONE, cur_ind - ONE), // cur_ind - maby -2. TODO
						apos[cur_ind]));
					temp.clear();
					for (int j = 0; j < true_parent.size(); j++)
					{
						temp.push_back(true_parent[j] + type_ind);
					}
					true_parent = HocHelpFunc::Find(HocHelpFunc::VectorSmallerComparison(
						apos[cur_ind], HocHelpFunc::SubVector(breaks, temp)));

					if (HocHelpFunc::Find(HocHelpFunc::VectorSmallerComparison(ONE, true_parent)).size() != ZERO)
					{
						adopted.push_back(i);
					}
					// stopped at line 85 in matlab

				}
				if (adopted.size() != ZERO)
				{
					childs_inds.erase(childs_inds.begin() + adopted[ZERO]);
				}

				if (childs_inds.size() == ZERO && ind == ONE)
				{
					childs_inds = HocHelpFunc::Find(HocHelpFunc::VectorComparison(apos, node_break));
				}
				vector<int> cur_seg;
				for (int i = 0; i < childs_inds.size(); i++)
				{
					int cur_child = childs_inds[i];
					int child_start = apos[cur_child];
					
					int parent_start;
					if (type_ind == ONE)
					{
						parent_start = 1;
					}
					else
					{
						parent_start = apos[type_ind];
					}
					cur_seg.push_back(child_start - parent_start);
				}
				child_seg = HocHelpFunc::ConnectVectors(child_seg, HocHelpFunc::FlipLr(cur_seg));
				if (childs_inds.size() != ZERO)
				{
					q = HocHelpFunc::ConnectVectors(q, HocHelpFunc::FlipLr(childs_inds));
					parent = HocHelpFunc::ConnectVectors(parent, (HocHelpFunc::HomoVecNum(childs_inds.size(), ONE * ind)));
				}
				ind++;
			}
			q = HocHelpFunc::SubVector(q, 1, q.size() - ONE);
		}
	}
	else
	{
		types = type;
	}

	type = types;

	getline(src, line);

	while (line.size() != ZERO)
	{

	}

}

*/