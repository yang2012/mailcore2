//
//  HTMLCleaner.cpp
//  mailcore2
//
//  Created by DINH Viêt Hoà on 2/3/13.
//  Copyright (c) 2013 MailCore. All rights reserved.
//

#include "MCHTMLCleaner.h"

#include "MCString.h"
#include "MCData.h"

#include <tidy.h>
#include <buffio.h>

#include "MCUtils.h"
#include "MCLog.h"

using namespace mailcore;

String * HTMLCleaner::cleanHTML(String * input)
{
    TidyBuffer output;
    TidyBuffer errbuf;
    TidyBuffer docbuf;
    int rc;

    TidyDoc tdoc = tidyCreate();
    tidyBufInit(&output);
    tidyBufInit(&errbuf);
    tidyBufInit(&docbuf);
    
    Data * data = input->dataUsingEncoding("utf-8");
    tidyBufAppend(&docbuf, data->bytes(), data->length());
    
    tidyOptSetBool(tdoc, TidyXhtmlOut, yes);
    tidySetCharEncoding(tdoc, "utf8");
    tidyOptSetBool(tdoc, TidyForceOutput, yes);
    rc = tidySetErrorBuffer(tdoc, &errbuf);
    if ((rc > 1) || (rc < 0)) {
        fprintf(stderr, "error tidySetErrorBuffer: %i\n", rc);
        fprintf(stderr, "1:%s", errbuf.bp);
        //return NULL;
    }
    rc = tidyParseBuffer(tdoc, &docbuf);
    //MCLog("%s", MCUTF8(input));
    if ((rc > 1) || (rc < 0)) {
        fprintf(stderr, "error tidyParseBuffer: %i\n", rc);
        fprintf(stderr, "1:%s", errbuf.bp);
        //return NULL;
    }
    rc = tidyCleanAndRepair(tdoc);
    if ((rc > 1) || (rc < 0)) {
        fprintf(stderr, "error tidyCleanAndRepair: %i\n", rc);
        fprintf(stderr, "1:%s", errbuf.bp);
        //return NULL;
    }
    rc = tidySaveBuffer(tdoc, &output);
    if ((rc > 1) || (rc < 0)) {
        fprintf(stderr, "error tidySaveBuffer: %i\n", rc);
        fprintf(stderr, "1:%s", errbuf.bp);
    }
    
    String * result = String::stringWithUTF8Characters((const char *) output.bp);
    
    tidyBufFree(&output);
    tidyBufFree(&errbuf);
    tidyRelease(tdoc);
    
    return result;
    
    /*
    if ( ok ) {
        rc = tidySetErrorBuffer( tdoc, &errbuf );      // Capture diagnostics
    }
    if ( rc &gt;= 0 ) {
        rc = tidyParseString( tdoc, input );           // Parse the input
    }
    if ( rc &gt;= 0 ) {
        rc = tidyCleanAndRepair( tdoc );               // Tidy it up!
    }
    if ( rc &gt;= 0 ) {
        rc = tidyRunDiagnostics( tdoc );               // Kvetch
    }
    if ( rc &gt; 1 ) {                                    // If error, force output.
        rc = ( tidyOptSetBool(tdoc, TidyForceOutput, yes) ? rc : -1 );
    }
    if ( rc &gt;= 0 ) {
        rc = tidySaveBuffer( tdoc, &output );          // Pretty Print
    }
     */
    
    /*
    if ( rc &gt;= 0 )
    {
        if ( rc &gt; 0 )
            printf( "\\nDiagnostics:\\n\\n\%s", errbuf.bp );
            printf( "\\nAnd here is the result:\\n\\n\%s", output.bp );
            }
    else
        printf( "A severe error (\%d) occurred.\\n", rc );
        
        tidyBufFree( &amp;output );
        tidyBufFree( &amp;errbuf );
        tidyRelease( tdoc );
        return rc;
     */
}
