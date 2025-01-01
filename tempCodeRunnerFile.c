int input;
    printf("Number of Roads: ");
    scanf("%d",&input);
    List **firstMap = createRoadMap(input);
    display(firstMap,input);