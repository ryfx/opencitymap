
print ("name: " + model.getName()  );
print("minimums and maximums:");
print( "\tlatitude: " + model.getMinLatitude() + " - " + model.getMaxLatitude() );
print( "\tlongitude: " + model.getMinLongitude() + " - " + model.getMaxLongitude() );
print();

nodes = model.getNodes();

for( i in nodes )
{
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
