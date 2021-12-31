#ifndef JSON_API
#define JSON_API

#include <json\value.h>
#include <json\json.h>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

/* Error codes that will be printed if error happend  */
enum ErrorCodes
{
    SUCCESS = 0,
    READING_JSON_ERROR,
    TOPOLOGY_HAS_NO_ID,
    TOPOLOGY_HAS_NO_COMPONENTS,
    EMPTY_JSON_FILE,
    WRITING_JSON_ID_NOT_FOUND,
    EMPTY_SJON_LIST,
    TOPOLOGY_ID_NOT_FOUND,
    COMPONENT_NOT_FOUND,
    NETLIST_IS_EMPTY
};




/*
    Class : Component
    Description: Class to hold information about each topology compoenent 
    Private data: 
        id: Id of the component
        type: Type of the component ex: nmos or resistor
        description: Holds the description of the component in the json format 
        netlist: holds the netlist of the component in the json format 

    Public Members:
        Constructor component: initializing Component object
        string get_type():  return the type of the component object
        string get_id():    return the id of the component object
        int get_netlist(vector<string>& vector): function to fill an empty vector with the netlist of the component object
                                                return errorCode : 0 if success  else if error happpened

*/
class Component
{
    string id;
    string type;
    Json::Value description;
    Json::Value netlist;

public:
    Component(string d, string t, Json::Value des, Json::Value n);
    string get_type();
    string get_id();
    int get_netlist(vector<string>& vector);
};

/*
Class : Topology 
Description: Class to hold information about each topology 
Private data:
    id: Id of the topology
    components: vector of all components in the topology 

Public Members:
    void Set_id():      Sets the id of the component object
    string get_id():    return the id of the component object
    void add_Component(string d, string type, Json::Value netlis, Json::Value component): function to add component in the vector of components and return 0 if success 
    void set_json_format(Json::Value f): Function to save the json format of the topology
    Json::Value get_json_format();: Function the get the json format of the topology
    int get_components(vector<string>& vector): Function to get all components names in the topology 
    int get_netlist(vector<string>& vector): function to fill an empty vector with the netlist of the component object
                                            return errorCode : 0 if success  else if error happpened

*/
class Topology
{
    string id;
    vector<Component> components;
    Json::Value json_format;

public:
    void Set_Id(string d);
    void add_Component(string d, string type, Json::Value netlis, Json::Value component);
    void set_json_format(Json::Value f);
    string Get_Id();
    Json::Value get_json_format();
    int get_components(vector<string>& vector);
    int get_netlist(string netlistId, vector<string>& vector);
};








/**********************************************************************************************************
    Function name: readJSON
    Description : Reading JSON file from system and save it to MyTopologyList
                : Assuming JSON file is in the same directory
    Inputs:     String File name
    return:     0 if reading is done successfully else return error code

***************************************************************************************************************/
int  readJSON(string FileName);



/************************************************************************************************
    Function name: writeJson
    Description : Writing topology with the given ID to json file (result.json)
                : result.json JSON file is in the same directory
    Inputs:     : Topology ID
    return:     : 0 if Writing is done successfully else return error code  if ID is not found

****************************************************************************************************/
int writeJson(string TopologyId);


/************************************************************************************************
    Function name: GetTopologyList
    Description :  Function to get all savd Topologeies
    Inputs:     : Vector of strings of size 0
    output      : Filled vector with the same of saved topologies
    warning     : Input vector should declared as: vector<string> vector; dont give it initial size
    return:     : 0 if copying is done successfully else return error code  no Topologies exist in the memory
****************************************************************************************************/
int GetTopologyList(vector<string>& vector);

/************************************************************************************************
Function name: DeleteTopology
Description :  Function to Delete topology with given ID form memory
Inputs:     : Topology ID
output      : None
warning     : Input vector should declared as: vector<string> vector; dont give it initial size
return:     : 0 if Deletion is done successfully else return error code  no Topologies exist with the given ID or List is empty
****************************************************************************************************/
int DeleteTopology(string TopologyId);


/***************************************************************************************************************
Function name: TopologyDevices
Description  :  Function to get all devices connected to the topology with the given ID
Inputs:      : Topology ID
output       : None
return:      : 0 if Deletion is done successfully else return error code  no Topologies exist with the given ID or List is empty.
****************************************************************************************************************/
int TopologyDevices(string TopologyId, vector<string>& devices);


/***************************************************************************************************************
Function name: TopologyDevices
Description  : Function to get all devices connected to the topology with the given ID
Inputs:      : Topology ID
output       : devices : devices connected to topology with the given ID
return:      : 0 if Deletion is done successfully else return error code  no Topologies exist with the given ID or List is empty.
****************************************************************************************************************/
int DeviceNetlist(string TopologyId, string DeviceId, vector<string>& netlist);




#endif