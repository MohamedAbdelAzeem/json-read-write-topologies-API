

#include "jsonAPI.h"

using namespace std;


int main() {


    Json::StyledStreamWriter writer; //for writing in json files

   //Testing Reader function
    int returnCode = READING_JSON_ERROR;
    if ((returnCode = readJSON("items.json")) != 0)
    {
        cout << "Error code :" << returnCode << endl;
    }


    /* Testing Topology devices Function */
    /*  returnCode = TOPOLOGY_ID_NOT_FOUND;
       vector<string> vect;
       if ((returnCode = TopologyDevices("top1", vect)) != 0)
       {
           cout << "Error code :" << returnCode << endl;
       }
      */

    /* Testing Device netlist function */
    returnCode = NETLIST_IS_EMPTY;
    vector<string> vect;
    if ((returnCode = DeviceNetlist("top1", "m1", vect)) != 0)
    {
        cout << "Error code :" << returnCode << endl;
    }

    /* Printing results */
    for (int i = 0; i < vect.size(); i++)
    {
        cout << vect[i] << endl;
    }

   /* Testing Delete Topology  */
   /* returnCode = TOPOLOGY_ID_NOT_FOUND;
    if ((returnCode = DeleteTopology("top1")) != 0)
    {
        cout << "Error code :" << returnCode << endl;
    }*/

    /* Testing Writing Function  */
    returnCode = WRITING_JSON_ID_NOT_FOUND;
    if ((returnCode = writeJson("top1")) != 0)
    {
        cout << "Error code :" << returnCode << endl;
    }


    return 0;
}