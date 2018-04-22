#include <iostream>
using namespace std;
#include <sqlite3.h>

int main(){

//#define SQLITE_OPEN_READONLY         0x00000001  /* Ok for sqlite3_open_v2() */
//#define SQLITE_OPEN_READWRITE        0x00000002  /* Ok for sqlite3_open_v2() */
//#define SQLITE_OPEN_CREATE           0x00000004  /* Ok for sqlite3_open_v2() */
//#define SQLITE_OPEN_URI              0x00000040  /* Ok for sqlite3_open_v2() */
//#define SQLITE_OPEN_MEMORY           0x00000080  /* Ok for sqlite3_open_v2() */
//#define SQLITE_OPEN_NOMUTEX          0x00008000  /* Ok for sqlite3_open_v2() */
//#define SQLITE_OPEN_FULLMUTEX        0x00010000  /* Ok for sqlite3_open_v2() */
//#define SQLITE_OPEN_SHAREDCACHE      0x00020000  /* Ok for sqlite3_open_v2() */
//#define SQLITE_OPEN_PRIVATECACHE     0x00040000  /* Ok for sqlite3_open_v2() */
//#define SQLITE_OPEN_WAL              0x00080000  /* VFS only */
/*These bit values are intended for use in the 3rd parameter to the
 sqlite3_open_v2() interface and in the 4th parameter to the sqlite3_vfs.xOpen method.*/
    
    /*Following C code segment shows how to connect to an existing database.
      If the database does not exist, then it will be created and finally a
      database object will be returned.*/
    
    cout << "sqlite3_open test.db"  <<endl;
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    rc = sqlite3_open("test.db", &db);
    if( rc ) {
        cout << "Can't open database" << sqlite3_errmsg(db) <<endl;
        return(0);
    } else {
        cout << "Opened database successfully" << endl;
    }
    sqlite3_close(db);
    
    //open v2
    cout << "sqlite3_open test1.db"  <<endl;
    sqlite3 *db_v2;
    int rc2 =  sqlite3_open_v2("test.db", &db_v2, SQLITE_OPEN_READONLY, NULL);
    if( rc2 ) {
        cout << "Can't open database" << sqlite3_errmsg(db_v2) <<endl;
        return(0);
    } else {
        cout << "Opened database successfully" << endl;
    }
    sqlite3_close(db_v2);
    
    
    
    return 0;
}
