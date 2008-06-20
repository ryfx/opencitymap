print ("name: " + model.getName()  );
print( "max latitude: " + model.getMaxLatitude() );
print( "max longitude: " + model.getMaxLongitude() );

nodes = model.getNodes();

for( i in nodes )
{
    //do stuff
    print("node " + i + " : " + nodes[i].latitude + " : " + nodes[i].longitude);
    print("\ttimestamp: " + nodes[i].timestamp);
    print("\ttags: ");
    tags = nodes[i].tags;
    for( key in tags )
    {
        print("\t\t" + key + " : " + tags[key]);
    }
    print();
}