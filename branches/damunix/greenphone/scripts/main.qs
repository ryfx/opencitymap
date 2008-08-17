nodes = mapmodel.getNodes();

var findAmenities = new Array();
var amenities = new Array("place_of_worship", "pub", "restaurant", "school", "bus", "hospital");
var nodeMap = new Array();
var nodeMapInversed = new Array();
var fase = "start";


script.setGameMenuTitle("Find");

for (amenity in amenities)
{
    script.addMenuItem(amenities[amenity]);
}
gameMenu["triggered"].connect(menuTrigger);



function menuTrigger(qAction)
{
    var displayableAmenityList = new Array();
    findAmenities[1] = "____";
    findAmenities[2] = "____";
    switch (qAction.text)
    {   
        case "hospital":
            findAmenities[0] = "hospital";
            break;
            
        case "place_of_worship":
            findAmenities[0] = "place_of_worship";
            break;
            
        case "pub":
            findAmenities[0] = "pub";
            findAmenities[1] = "biergarten";
            findAmenities[2] = "cafe";
            
            break; 
            
        case "restaurant":
            findAmenities[0] = "restaurant";
            break;
            
        case "school":
            findAmenities[0] = "school";
            findAmenities[1] = "university";
            break; 
            
        case "bus":
            findAmenities[0] = "bus_stop";
            findAmenities[1] = "bus_station";
            break; 

        default:
            break;
            
            //print("Menu \"" + __qt_sender__.title +"\" " + "pressed with item: " + obj.text);
    }
    
    // __qt_sender__ shows hich menu is triggered.
    // obj is the QAction of the menu that is triggered.

        
    /*    
    for (i = 1; i <= busNumber; ++i)
    {
        if (qAction.text == ("bus_stop" + i))
        {
            print("Going to bus " + i);
        }
    }
    */
    
    var numberOfResults = 0;
    nodeMap = [];
    for( i in nodes )
    {
        tags = nodes[i].tags;
        for( key in tags )
        {
            

            if ((tags[key] == findAmenities[0]) || (tags[key] == findAmenities[1]) || (tags[key] == findAmenities[2]))
            {
                var displayName = findAmenities[0] + (numberOfResults + 1) + ": ";
                nodeMap[numberOfResults] = i;
                nodeMapInversed[nodes[i].address] = displayName;
                displayableAmenityList[numberOfResults] = displayName;
                
                //print ("NodeMap["+numberOfResults+"] = " + i);  
                
                for( varName in tags )
                {
                    if (varName == "name")
                    {
                        nodeMapInversed[nodes[i].address] += tags[varName];
                        displayableAmenityList[numberOfResults] += tags[varName];
                    }
                }
                numberOfResults++; 
            }
        }
    }
    
    if (numberOfResults > 0)
        script.dispListView(displayableAmenityList); 
    else
        script.showMessage("No results found", "No " + findAmenities[0] + "s found");
        
        
    listViewMenu["triggered"].connect(listViewMenuTrigger);
}


function listViewMenuTrigger(obj)
{
    //print("Menu \"" + __qt_sender__.title +"\" " + "pressed " + obj.text);
    destinations = script.listViewSelectedIndexes();
    for (destination in destinations)
    { 
        if (destinations[destination])
        {
            //print("going to dest: " + destination + " nodeNr: " + nodeMap[destination]);
            script.addHighlightNode(nodeMap[destination]);
        }        
    }
    script.clearListView();
    
    script.showMessage("Arrows will lead you!", "Follow the red arrows and you'll arrive at the chosen place(s)");
    if (fase == "start")
    {
        highlightnode["destinationReach"].connect(destinationReached);
        fase = "find";
    }
    
    listViewMenu["triggered"].disconnect(listViewMenuTrigger);
}




function destinationReached(node)
{
    //script.removeHighlightNode(node);
    script.showMessage("Destination reached", "Arrived at " + nodeMapInversed[node.address]);
}

