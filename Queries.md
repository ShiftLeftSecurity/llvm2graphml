# Some example queries

 - List all modules:

    ```
    g.V().hasLabel('module').valueMap().unfold()
    ```

 - List all functions:

    ```groovy
    g.V().hasLabel('function').valueMap().unfold()
    ```

 - Count all the instructions:

    ```groovy
    g.V().hasLabel('instruction').groupCount().by('opcode').unfold()
    ```

 - List the types:

    ```groovy
    g.V().hasLabel('type').valueMap().unfold()
    ```
   
 - List function names that take 'x' as an argument:
 
    ```groovy
    g.V().has('argument', 'name', 'x').out('function').valueMap('name')
    ```
