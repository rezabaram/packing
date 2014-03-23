#include <iostream>
#include <fstream>
#include <vector>
#include <Eigen>
#include"sphere.h"
#include"packing.h"
#include"polygons.h"
//#include"pure_pack.h"
//#include"mesh.h"
//#include"solids.h"

using namespace Eigen;
using namespace std;

//using vec3d=vec<3>;

int main()
{

Packing<2> pack = polygon_packing(3);
//Packing pack = pure_packing(4);

pack.generate(500,0.002);
//cerr<<pack.invs.back().dot(pack.inits[0])<<endl;

return 0;

}
/*
void test(){
Solid solid;

//solid.read_vertices();
for(auto i=0; i<10; i++){
	//solid.add_vertex(VectorXd::Random(3));
	}

ifstream input("tetrahedron.sld");
solid.parse(input);
solid.print_vertices();
solid.print_faces();
}
*/
