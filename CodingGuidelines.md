# Coding guidelines #
**Indentation: Use spaces (4) instead of tabs;**

```
    # Tabs can have different lengths on different machines
```

**Member variables must begin with m\_variableName
```
class MapModel
{
    private:
        // Private attributes

        QList<Node*> m_nodes;
        QList<Way *> m_ways;
```**

**Indent the right amount
```
    # See example above
```**

**Use spaces between arguments of a function, but not after function name
```
    void setNodes( QList<Node*> new_var );
```**

**Show the word wrap line (don't exceed 100 chars per line!)**

**Haakjes start at new line**

```
    if (file.error()) {
        qDebug()  << "Error: Cannot write file "<< fileName <<": "<< file.errorString();
    }
```

