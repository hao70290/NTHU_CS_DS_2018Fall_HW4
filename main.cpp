#include <iostream>
#include "function.h"
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    Implement inst = *(new Implement());

    string command;
    int n_vert;
    cin >> n_vert;
    inst.Allocate_vertexMem(n_vert);

    while(cin>> command){

        int v1 , v2 , w;

        if(command == "add"){
            cin>>v1>>v2>>w;
            inst.addEdge(v1,v2,w);
        }else if(command == "shortest_path"){
            cin>>v1>>v2;
            cout<<inst.shortest_path(v1 , v2)<<endl;
        }else if(command == "mst_weight"){

            cout<<inst.mst_weight()<<endl;

        }else if(command == "two_color"){
            bool able = inst.two_colorable();
            if(able){
                cout<<"two-colorable"<<endl;
            }else{
                cout<<"not two-colorable"<<endl;
            }
        }
    }

    return 0;
}
