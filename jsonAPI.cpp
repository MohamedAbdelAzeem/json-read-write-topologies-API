

#include "jsonAPI.h"

using namespace std;

typedef std::vector<std::string> Members;

vector<Topology>  MyTopologyList;


                                      
/* Component class function definitions */
Component:: Component(string d, string t, Json::Value des, Json::Value n)
{
    id = d;
    type = t;
    description = des;
    netlist = n;
}

string Component::get_type()
{
    return type;
}

string Component::get_id()
{
    return id;
}

int Component:: get_netlist(vector<string>& vector)
{
    int returnCode = SUCCESS;
    if (netlist.size() == 0)
    {
        return  NETLIST_IS_EMPTY;
    }
    Members netlist_members = netlist.getMemberNames();
    for (int i = 0; i < netlist.size(); i++)
    {
        vector.push_back(netlist[netlist_members[i]].asString());
    }
    return returnCode;
}







/* Topology class function definitions  */
void Topology::Set_Id(string d)
{
    id = d;
}


void Topology::add_Component(string d, string type, Json::Value netlis, Json::Value component)
{
    Component c(d, type, component, netlis);
    components.push_back(c);
}

void Topology::set_json_format(Json::Value f)
{
    json_format = f;

}

string Topology::Get_Id()
{
    return id;
}

Json::Value Topology::get_json_format()
{
    return json_format;
}


int Topology::get_components(vector<string>& vector)
{
    if (components.size() == 0)
    {
        return TOPOLOGY_HAS_NO_COMPONENTS;
    }
    for (int i = 0; i < components.size(); i++)
    {
        vector.push_back(components[i].get_type());
    }
    return SUCCESS;
}


int Topology::get_netlist(string netlistId, vector<string>& vector)
{
    if (components.size() == 0)
    {
        return TOPOLOGY_HAS_NO_COMPONENTS;
    }

    int returnCode = SUCCESS;
    int componentPosition = 0;
    for (int i = 0; i < components.size(); i++)
    {
        if (components[i].get_id() == netlistId)
        {
            componentPosition = i;
            returnCode = SUCCESS;
        }
        else
        {
            returnCode = COMPONENT_NOT_FOUND;
        }
    }

    if (returnCode == SUCCESS)
    {

        returnCode = components[componentPosition].get_netlist(vector);
    }
    return SUCCESS;
}


/**********************************************************************************************************
    Function name: readJSON
    Description : Reading JSON file from system and save it to MyTopologyList
                : Assuming JSON file is in the same directory
    Inputs:     String File name
    return:     0 if reading is done successfully else return error code

***************************************************************************************************************/
int  readJSON(string FileName)
{
    Json::Reader reader;  //for reading the data
    Json::Value Value; //for modifying and storing new values
    //opening file using fstream
    ifstream file(FileName);
    // check if there is any error is getting data from the json file
    if (!reader.parse(file, Value)) {
        // cout << reader.getFormattedErrorMessages();
        return  READING_JSON_ERROR;
    }

    if (Value.empty())
    {
        return  EMPTY_JSON_FILE;

    }
    //Creat object to store JSON values for the current topology
    Topology newTop;
    /* Check if topology has id member */
    if (Value.isMember("id"))
    {
        newTop.Set_Id(Value["id"].asString());
    }
    else
    {
        return  TOPOLOGY_HAS_NO_ID;
    }

    /* Check if topolgy has components member and it is not empty  */
    if (Value.isMember("components"))
    {

        /* Adding each component individually */
        for (int component = 0; component < Value["components"].size(); component++)
        {
            Members newTop_members = Value["components"][component].getMemberNames();
            string descriptionName;
            for (int i = 0; i < newTop_members.size(); i++)
            {
                if (newTop_members[i] != "id" && newTop_members[i] != "netlist" && newTop_members[i] != "type")
                {
                    descriptionName = newTop_members[i];
                }
            }
            string id = Value["components"][component]["id"].asString();
            string type = Value["components"][component]["type"].asString();
            Json::Value   netlist = Value["components"][component]["netlist"];
            Json::Value   descirption = Value["components"][component][descriptionName];
            newTop.add_Component(id, type, netlist, descirption);
        }
    }
    else
    {
        return  TOPOLOGY_HAS_NO_COMPONENTS;
    }

    newTop.set_json_format(Value);
    MyTopologyList.push_back(newTop);
    return SUCCESS;

}


/************************************************************************************************
    Function name: writeJson
    Description : Writing topology with the given ID to json file (result.json)
                : result.json JSON file is in the same directory
    Inputs:     : Topology ID
    return:     : 0 if Writing is done successfully else return error code  if ID is not found

****************************************************************************************************/
int writeJson(string TopologyId)
{
    Json::Value newValue;
    int returnCode = SUCCESS;

    unsigned int TopologyListSize = MyTopologyList.size();
    if (TopologyListSize == 0)
    {
        returnCode = EMPTY_SJON_LIST;
        return returnCode;
    }
    for (int i = 0; i < TopologyListSize; i++)
    {
        if (MyTopologyList[i].Get_Id() == TopologyId)
        {
            newValue = MyTopologyList[i].get_json_format();
            break;
        }
        returnCode = WRITING_JSON_ID_NOT_FOUND;
    }


    if (returnCode == SUCCESS)
    {
        Json::StyledStreamWriter writer; //for writing in json files
        ofstream newFile;
        newFile.open("result.json");
        writer.write(newFile, newValue);
    }


    return returnCode;
}

/************************************************************************************************
    Function name: GetTopologyList
    Description :  Function to get all savd Topologeies
    Inputs:     : Vector of strings of size 0
    output      : Filled vector with the same of saved topologies
    warning     : Input vector should declared as: vector<string> vector; dont give it initial size
    return:     : 0 if copying is done successfully else return error code  no Topologies exist in the memory
****************************************************************************************************/
int GetTopologyList(vector<string>& vector)
{

    int MyListSize = MyTopologyList.size();
    if (MyListSize == 0)
    {
        return EMPTY_SJON_LIST;
    }

    /* Copying MyToplogyList to input vector */
    for (int iterator = 0; iterator < MyListSize; iterator++)
    {
        vector.push_back(MyTopologyList[iterator].Get_Id());
    }
    return SUCCESS;

}

/************************************************************************************************
Function name: DeleteTopology
Description :  Function to Delete topology with given ID form memory
Inputs:     : Topology ID
output      : None
warning     : Input vector should declared as: vector<string> vector; dont give it initial size
return:     : 0 if Deletion is done successfully else return error code  no Topologies exist with the given ID or List is empty
****************************************************************************************************/
int DeleteTopology(string TopologyId)
{
    int MyListSize = MyTopologyList.size();
    if (MyListSize == 0)
    {
        return EMPTY_SJON_LIST;
    }

    int returnCode = SUCCESS;
    int IdPosition = 0;
    for (int iterator = 0; iterator < MyListSize; iterator++)
    {
        if (MyTopologyList[iterator].Get_Id() == TopologyId)
        {
            IdPosition = iterator;
            returnCode = SUCCESS;
        }
        else
        {
            returnCode = TOPOLOGY_ID_NOT_FOUND;
        }
    }

    auto vectorIterator = MyTopologyList.begin() + IdPosition;
    if (returnCode == SUCCESS)
    {
        MyTopologyList.erase(vectorIterator);
    }

    return  returnCode;
}



/***************************************************************************************************************
Function name: TopologyDevices
Description  :  Function to get all devices connected to the topology with the given ID
Inputs:      : Topology ID
output       : None
return:      : 0 if Deletion is done successfully else return error code  no Topologies exist with the given ID or List is empty.
****************************************************************************************************************/
int TopologyDevices(string TopologyId, vector<string>& devices)
{
    int MyListSize = MyTopologyList.size();
    if (MyListSize == 0)
    {
        return EMPTY_SJON_LIST;
    }

    int returnCode = SUCCESS;
    int IdPosition = 0;
    for (int iterator = 0; iterator < MyListSize; iterator++)
    {
        if (MyTopologyList[iterator].Get_Id() == TopologyId)
        {
            IdPosition = iterator;
            returnCode = SUCCESS;
        }
        else
        {
            returnCode = TOPOLOGY_ID_NOT_FOUND;
        }
    }

    if (returnCode == SUCCESS)
    {
        /* Put components in devices array */
        returnCode = MyTopologyList[IdPosition].get_components(devices);

    }

    return  returnCode;
}


/***************************************************************************************************************
Function name: TopologyDevices
Description  : Function to get all devices connected to the topology with the given ID
Inputs:      : Topology ID
output       : devices : devices connected to topology with the given ID
return:      : 0 if Deletion is done successfully else return error code  no Topologies exist with the given ID or List is empty.
****************************************************************************************************************/
int DeviceNetlist(string TopologyId, string DeviceId, vector<string>& netlist)
{
    int MyListSize = MyTopologyList.size();
    if (MyListSize == 0)
    {
        return EMPTY_SJON_LIST;
    }

    int returnCode = SUCCESS;
    int IdPosition = 0;
    for (int iterator = 0; iterator < MyListSize; iterator++)
    {
        if (MyTopologyList[iterator].Get_Id() == TopologyId)
        {
            IdPosition = iterator;
            returnCode = SUCCESS;
        }
        else
        {
            returnCode = TOPOLOGY_ID_NOT_FOUND;
        }
    }

    if (returnCode == SUCCESS)
    {
        /* Put components in devices array */
        returnCode = MyTopologyList[IdPosition].get_netlist(DeviceId, netlist);

    }

    return returnCode;
}