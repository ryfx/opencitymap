# QtScript #
What possibilities does QtScript has to offer you and how to use it?
  * Starting
  * Customizing the menu
  * MessageBox
  * ListView
  * Higlighting Nodes
  * Using the mapModel (not yet written)

## Starting ##
Pretty easy just write some QtScript in the main.qs file.
The script is called when you select "start script" in the menu.

## Customizing the menu ##
QtScript has its own menu which can be customized at wish.

**You can create a slot for the gameMenu like this:**
```
function menuTrigger(obj)
{
    // __qt_sender__ shows hich menu is triggered.
    // obj is the QAction of the menu that is triggered.
    
    switch (obj.text)
    {
        case "menuItem1":
            //Do something
            break;
            
        case "menuItem2":
            //Do something else
            break;
          
        default:
            print("Menu \"" + __qt_sender__.title +"\" " + "pressed with item: " + obj.text);
    }
}
   
gameMenu["triggered"].connect(menuTrigger);
```
**You can add gameMenu items like this:**
```
script.addMenuItem("newMenuItem");
```
**You can remove gameMenu items like this:**
```
script.removeMenuItem("oldMenuItem");
```
**You can clear the entire gameMenu like this:**
```
script.clearMenu();
```

## Higlighting Nodes ##
Hightlighting a Node means displaying a small (red) arrow on the map in the direction of that Node.
The distance will also be showed.
```
script.addHighlightNode(NodeNr);
highlightnode["destinationReach"].connect(destinationReached);

function destinationReached(node)
{
    //Do something
}
```

## MessageBox ##
Sending a messageBox is the easiest thing you can do from script.
```
script.showMessage("Title", "Message ");
```


## ListView ##
```
var listViewArray = new Array("Item1", "Item2", "Item3");
script.dispListView(listViewArray); 
listViewMenu["triggered"].connect(listViewTrigger);

function listViewMenuTrigger()
{
    listViewSelected = script.listViewSelectedIndexes();
    for (selected in listViewSelected)
    { 
        if (listViewSelected[selected])
        {
            //Do something with selected Item
        }        
    }
    script.clearListView();
    listViewMenu["triggered"].disconnect(listViewTrigger);
}
```