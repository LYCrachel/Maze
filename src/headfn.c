/*
 * ****************************************************************************
 *
 * PROJECT:     Servrian
 *
 * TITLE:       
 *
 * FUNCTION:    serve_head: This is the function that elaborates the header of
 *              a response, it takes two arguments: the client's connection
 *              and the file requested in the HEAD message.
 *
 * INPUTS:
 *
 * OUTPUTS:
 *
 * AUTHOR:      Brian Mayer blmayer@icloud.com
 *
 * NOTES:
 *
 * COPYRIGHT:   All rigths reserved. All wrongs deserved. (Peter D. Hipson)
 *
 * ****************************************************************************
 */

#include "headfn.h"

int serve_head(int conn, struct header req, int encrypted) {
    
    /* Create the status variable     */
    int *status;
    
    /* Get the page file's size */
    int *page_size;
    *page_size = file_size(req.path);
    
    if(page_size > 0) {
        /* Something went wrong, problablay file was not found */
        *status = 404;
        *page_size = file_size("webpages/404.html");
    } else {
        *status = 200;
    }
    
    /* Create the head */
    char *head = create_response(req, encrypted);
    
    /* Send the head */
    write(conn, head, strlen(head));
    
    printf("\tHead for %s served.\n", req.path);
    
    return 0;
}
