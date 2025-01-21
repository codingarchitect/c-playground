#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/encoding.h>

static int gvar1 = 0;

char *XAXmlGetCurrentNodeValue() {
    int             inLen;
	int             outLen;
    char            *dataPrefix = "test";
    char            *data;
    static char     *outData = NULL;
    static int      callCount = 0;

    callCount++;
    inLen = strlen(dataPrefix) + 1;
    data = malloc((inLen + 1) * sizeof(char));
    snprintf(data, inLen + 1, "%s%d%c", dataPrefix, callCount, '\0'); 

    inLen = strlen (data);

	if (inLen==0)
		return (data);

	outLen = inLen;

	if (outData) {
        printf("XAXmlGetCurrentNodeValue - outData pointer value before free: %p\n", outData);    
        printf("XAXmlGetCurrentNodeValue - outData char value before free: %s\n", outData);
        free(outData);
        outData = NULL;
        printf("XAXmlGetCurrentNodeValue - outData pointer value after free: %p\n", outData);    
        printf("XAXmlGetCurrentNodeValue - outData char value after free: %s\n", outData);
    }
    else {
        printf("XAXmlGetCurrentNodeValue - outData is NULL, first call\n");
    }

    outData = malloc((outLen + 1) * sizeof(char));
    printf("XAXmlGetCurrentNodeValue - outData pointer value after malloc: %p\n", outData);
    
    // snprintf(outData, 6, "%s%c", "test1", '\0'); 
	if (UTF8Toisolat1 ((xmlChar *)outData, &outLen, (xmlChar *)data, &inLen) < 0)
	 	puts("XAXmlGetCurentNodeValue call to UTF8Toisolat1 failed");
    *(outData + outLen) = '\0';
    printf("XAXmlGetCurrentNodeValue - outData pointer value after UTF8Toisolat1: %p\n", outData);    
    printf("XAXmlGetCurrentNodeValue - outData char value after UTF8Toisolat1: %s\n", outData);
    free(data);
    data = NULL;
    return (outData);
}

char *XAXmlGetCurrentNodeValue2() {
    int             inLen;
	int             outLen;
    char            *dataPrefix = "test";
    char            *data;
    static char     *outData = NULL;
    static int      callCount = 0;

    callCount++;
    inLen = strlen(dataPrefix) + 1;
    data = malloc((inLen + 1) * sizeof(char));
    printf("XAXmlGetCurrentNodeValue2 - data pointer value: %p\n", data);    
    snprintf(data, inLen + 1, "%s%d%c", dataPrefix, callCount, '\0'); 
    printf("XAXmlGetCurrentNodeValue2 - data char value: %s\n", data);    

    inLen = strlen (data);

	if (inLen==0)
		return (data);

	outLen = inLen;

	if (outData) {
        printf("XAXmlGetCurrentNodeValue2 - outData pointer value before malloc: %p\n", outData);    
        printf("XAXmlGetCurrentNodeValue2 - outData char value before malloc: %s\n", outData);
    }
    else {
        printf("XAXmlGetCurrentNodeValue2 - outData is NULL, first call\n");        
    }

    outData = malloc((outLen + 1) * sizeof(char));
    printf("XAXmlGetCurrentNodeValue2 - outData pointer value after malloc: %p\n", outData);
    
    // snprintf(outData, 6, "%s%c", "test1", '\0'); 
	if (UTF8Toisolat1 ((xmlChar *)outData, &outLen, (xmlChar *)data, &inLen) < 0)
	 	puts("XAXmlGetCurentNodeValue2 call to UTF8Toisolat1 failed");
    *(outData + outLen) = '\0';
    printf("XAXmlGetCurrentNodeValue2 - outData pointer value after UTF8Toisolat1: %p\n", outData);    
    printf("XAXmlGetCurrentNodeValue2 - outData char value after UTF8Toisolat1: %s\n", outData);
    free(data);
    data = NULL;
    return (outData);
}

void f1() {
    static int callCount = 0;
    callCount++;
    gvar1++;
    printf("f1 - gvar1: %d\n", gvar1);
    printf("f1 - callCount: %d\n", callCount);
}

void f2() {
    static int callCount = 0;
    static int gvar1 = 0;
    callCount++;
    gvar1++;
    printf("f2 - gvar1: %d\n", gvar1);
    printf("f2 - callCount: %d\n", callCount);
}

int main() {
    // Write C code here
    char* var1 = XAXmlGetCurrentNodeValue();
    // The free call below causes double free exception in the next call to XAXmlGetCurrentNodeValue
    // printf("Calling function XAXmlGetCurrentNodeValue call 1 - var1 pointer value before free: %p\n", var1);
    // if (var1)
    //     free(var1);
    // var1 = NULL;
    // printf("Calling function XAXmlGetCurrentNodeValue call 1 - var1 pointer value after free: %p\n", var1);
    var1 = XAXmlGetCurrentNodeValue();
    // The free call below causes double free exception in the next call to XAXmlGetCurrentNodeValue (if made)
    // printf("Calling function XAXmlGetCurrentNodeValue call 2 - var1 pointer value before free: %p\n", var1);
    // if (var1)
    //     free(var1);
    // printf("Calling function XAXmlGetCurrentNodeValue call 2 - var1 pointer value after free: %p\n", var1);
    
    printf("main - gvar1, before fx calls: %d\n", gvar1);
    f1();
    f1();
    f1();
    printf("main - gvar1, after 3 f1 calls: %d\n", gvar1);

    f2();
    f2();
    printf("main - gvar1, after 2 f2 calls: %d\n", gvar1);
    
    f1();
    f1();
    printf("main - gvar1, after 5 f1 calls: %d\n", gvar1);

    char *var2 = XAXmlGetCurrentNodeValue2();
    printf("Calling function XAXmlGetCurrentNodeValue2 call 1 - var2 pointer value before free: %p\n", var2);
    if (var2)
        free(var2);
    var2 = NULL;
    printf("Calling function XAXmlGetCurrentNodeValue2 call 1 - var2 pointer value after free: %p\n", var2);
    var2 = XAXmlGetCurrentNodeValue2();
    printf("Calling function XAXmlGetCurrentNodeValue2 call 2 - var2 pointer value before free: %p\n", var2);
    if (var2)
        free(var2);
    var2 = NULL;
    printf("Calling function XAXmlGetCurrentNodeValue2 call 2 - var2 pointer value after free: %p\n", var2);

    return 0;
}

