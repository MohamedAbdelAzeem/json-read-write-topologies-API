

#include "jsonAPI.h"

using namespace std;


int main() {


    Json::StyledStreamWriter writer; //for writing in json files


    int returnCode = READING_JSON_ERROR;
    if ((returnCode = readJSON("items.json")) != 0)
    {
        cout << "Error code :" << returnCode << endl;
    }


    /*  returnCode = TOPOLOGY_ID_NOT_FOUND;
       vector<string> vect;
       if ((returnCode = TopologyDevices("top1", vect)) != 0)
       {
           cout << "Error code :" << returnCode << endl;
       }
      */

    returnCode = NETLIST_IS_EMPTY;
    vector<string> vect;
    if ((returnCode = DeviceNetlist("top1", "m1", vect)) != 0)
    {
        cout << "Error code :" << returnCode << endl;
    }


    for (int i = 0; i < vect.size(); i++)
    {
        cout << vect[i] << endl;
    }


   /* returnCode = TOPOLOGY_ID_NOT_FOUND;
    if ((returnCode = DeleteTopology("top1")) != 0)
    {
        cout << "Error code :" << returnCode << endl;
    }*/

    returnCode = WRITING_JSON_ID_NOT_FOUND;
    if ((returnCode = writeJson("top1")) != 0)
    {
        cout << "Error code :" << returnCode << endl;
    }


    return 0;
}