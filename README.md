# text-app
A multi-platform text app with new ways on protecting privacy, and plugin API. (not yet available)

# The ways to transfer data

## Tunneling mode
Tunneling mode is the default mode for sending data.
In tunneling mode, data will not be saved in the server, not even temporary,
instead, data is directly transferred from client to client through a tunnel of the server.
This mode required both clients online which cause inconvenience.
So we can deploy a data server to solve this.
### Data server
The data server is a server that you trust or is deployed by yourself.
It should consume very little CPU usage
so that you can deploy it on pc or desktop without affecting the normal use of the computer.
Also, a public IP or domain is optional,
you can receive an id from the main server.

#### Data server receive data when client offline(client in data server)
It acts similar as a client,
but it does not the decryption code,
it simply temporarily receive the data for the client.
After the client is online,
the data will be received by the client.

#### Data server send data when client offline(client not in the main server)
It also acts similar to a client.
First,
it receives the send data from the client.
Then,
it temporarily saved it and wait until the receive client the data is online.
Lastly,
the main sever makes a tunnel between receive client and the data server,
the send data will be sent.

#### Data server send/receive data when clients online
It acts as a medium between the server and the client.
The main server will not know about the client directly,
the main server will only know it is a user under the data server,
So a double tunnel will happen,
a tunnel will be linked to the data server,
then the tunnel will link to a tunnel that the server made to connect to the client.
On these circumstances,
no data will be saved in both the main server and data server, not even temporary.

## Urgent mode
The urgent mode can be set for a chat or a single message(or file).
Urgent mode is not needed when you are already using a data server.
On urgent mode,
data will be sent to the main server,
the data will be temporarily saved by the server,
and be sent when the receive client is on.
This may not be safe for your data.

# The data
The data format should all be the same on sending files or text,
and also when communicating with servers(eg. calling to make a tunnel)

## Encrypting
reserved

## Data formating
### Login pass
The pass data to identify the user<br>
FORMAT: pass->pass_data<-pass<br>
pass: a code that server return on login request<br>
(need to be decrypted then encrypted)<br>
REQUIRE: All
### Header
#### Format
header->header<-header
#### Request: 
The request type for the data<br>
FORMAT: type:type;<br>
list of type: tunnel,pack,urgent,plugin,register,login<br>
tunnel: request to open tunnel(to main server or data server)<br>
pack: type to state that it carry text or file<br>
urgent: same as pack,but it will be process in urgent mode
plugin: request to plugin
register: requst to register a new user id
login: request a pass_data for login
(it returns with a encrypted form)
REQUIRE: All

#### Target: 
The target of the reciver<br>
FORMAT: target:mainserver: dataserver;<br>
mainserver: ip or domain<br>
dataserver: ip or domain or data_server_id(only needed if you use a data server)<br>
id: the id of the user<br><br>
REQUIRE: All(exclude plugin,pack,login,register)

#### Target(plugin): 
The target plugin api<br>
FORMAT: target:plugin_id;<br>
REQUIRE: plugin

#### Encryption of Header
It should be encrypted to be only can be read by the main server or data server.

### Body

#### Format
start->body<-end
#### Extra
Extra is extra information for handling the data
##### Format
extra->list of extra<-extra<br>
FORMAT: extra_type:infromation;
##### Extra types
###### data_type
inform the type of the data<br>
TYPES:<br>
text: text message<br>
file: file<br>
eg. data_type:text;
###### file_name
inform the name and the extension of the file<br>
eg. file_name:hello_world.exe;
###### plugin
extra information for plugin to handle<br>
FORMAT: plugin:plugin_name:information;<br>
information can be anything
#### Data
Data is the main content<br>
##### Format
data->data<-data

#### Encrypting for main server: 
Type: plugins,tunnel,login,register<br>
,start->,<-end
#### Encrypting for Client
Type: urgent,pack
reserved

# ROADMAP
14/1/2022 start to develop
