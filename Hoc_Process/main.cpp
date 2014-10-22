#include "Menu.h"
#include "Defs.h"

#include "HocHelpFunc.h"

// TODO - maby to get the dir path with the args.

int main(int argc, char *argv[])
{
	vector<int> a = { 1, 2, 0, 3, -6, 2 };
	/*vector<int> b = { 0, 2, 5 };

	/*HocHelpFunc::VectorComparison(a, b);
	HocHelpFunc::SubVector(a, 2, 5);

	vector<int> i;
	i.resize(3);
	i.at(2) = 4;
	
	int j = i[2];
	HocHelpFunc::VectorSmallerEqualsComparison(a, b);*/

	HocHelpFunc::Find(a);

	Menu menu = Menu(DEFULT_DIR_PATH);
	menu.MenuMain();
	
}


/************************************************************************
* Class name:
* The Input:
* The class operation:
*************************************************************************/


