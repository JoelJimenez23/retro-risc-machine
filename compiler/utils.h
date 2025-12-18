
char* file_to_string(FILE *fp, int *longitud_out) {
    int capacidad = 10;
    int longitud = 0;
    char *str = malloc(capacidad * sizeof(char));
    int c;

    if (!str) return NULL;

    while((c = fgetc(fp)) != EOF) {
        if(longitud + 1 >= capacidad) {
            capacidad *= 2;
            str = realloc(str, capacidad * sizeof(char));
        }
        str[longitud++] = c;
    }
    str[longitud] = '\0';
    *longitud_out = longitud; // Set the length via pointer
    return str; // Return the actual allocated memory
}

