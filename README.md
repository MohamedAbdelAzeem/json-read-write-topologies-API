# JSON API  task for master micro
## API is working on jsoncpp library to parse json files.
## how to build:
### 1- Download and unzip the project.
### 2- Open ```jsonAPI.sln``` in visual studio.
### 3- Change project include directory :
#### - go to project properties -> C/C++ -> General -> include directory-> add ```YOUR-PATH\include``` path.
### 4- build and run.

### API source file : jsonAPI.cpp
### API header file : jsonAPI.h

## API Functions:
```
**********************************************************************************************************
    Function name: readJSON
    Description : Reading JSON file from system and save it to MyTopologyList
                : Assuming JSON file is in the same directory
    Inputs:     String File name
    return:     0 if reading is done successfully else return error code

***************************************************************************************************************/
int  readJSON(string FileName);
```


```
/************************************************************************************************
    Function name: writeJson
    Description : Writing topology with the given ID to json file (result.json)
                : result.json JSON file is in the same directory
    Inputs:     : Topology ID
    return:     : 0 if Writing is done successfully else return error code  if ID is not found

****************************************************************************************************/
int writeJson(string TopologyId);
```
```
/************************************************************************************************
    Function name: GetTopologyList
    Description :  Function to get all savd Topologeies
    Inputs:     : Vector of strings of size 0
    output      : Filled vector with the same of saved topologies
    warning     : Input vector should declared as: vector<string> vector; dont give it initial size
    return:     : 0 if copying is done successfully else return error code  no Topologies exist in the memory
****************************************************************************************************/
int GetTopologyList(vector<string>& vector);
```

```
/************************************************************************************************
Function name: DeleteTopology
Description :  Function to Delete topology with given ID form memory
Inputs:     : Topology ID
output      : None
warning     : Input vector should declared as: vector<string> vector; dont give it initial size
return:     : 0 if Deletion is done successfully else return error code  no Topologies exist with the given ID or List is empty
****************************************************************************************************/
int DeleteTopology(string TopologyId);
```
```
/***************************************************************************************************************
Function name: TopologyDevices
Description  :  Function to get all devices connected to the topology with the given ID
Inputs:      : Topology ID
output       : None
return:      : 0 if is done successfully else return error code  no Topologies exist with the given ID or List is empty.
****************************************************************************************************************/
int TopologyDevices(string TopologyId, vector<string>& devices);
```
```
/***************************************************************************************************************
Function name: DeviceNetlist
Description  : Function to get all netlist devices connected to the topology with the given ID and given Component ID
Inputs:      : Topology ID, Component ID
output       :  netlist devices
return:      : 0 if is done successfully else return error code  no Topologies exist with the given ID or List is empty.
****************************************************************************************************************/
int DeviceNetlist(string TopologyId, string DeviceId, vector<string>& netlist);
```

## Testing is done manually through test.cpp.
