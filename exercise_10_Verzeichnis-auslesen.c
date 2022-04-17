#include <stdio.h>
#include <io.h>
#include <time.h>

/*Printed alle Dateien in dem Verzeichnis, in dem Datei liegt und gibt Anzahl aus*/
void main( void )
{
    struct _finddata_t c_file;
    long hFile;
    int counter = 0;

    /* Find first file in current directory */
    if( (hFile = _findfirst( "*.*", &c_file )) == -1L )
    {
       printf( "No files in current directory!\n" );
    }
    else
    {
      ++counter;
            printf( "Listing of all files\n\n" );
            printf( " %-12s \n", c_file.name );

            /* Find the rest of the .c files */
            while( _findnext( hFile, &c_file ) == 0 )
            {
               ++counter;
                printf( " %-12s \n", c_file.name );
            }

       _findclose( hFile );
    }

    printf( "Number of files: %d\n", counter );
}