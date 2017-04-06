#ifndef SQLITES_TEST_H
#define SQLITES_TEST_H

#include"../catch/catch.hpp"
#include"../../src/masternode/database/sqlmanager.h"


#include<iostream>
using namespace mocores;


bool getContent()
{
    SqlDatabase db=SqlManager::getConnection("sqlite3:data_frame.db");
    SqlConnection * con=db.getConnection();
    SqlQuery query(*con);
    query.exec("select * from node_info;");
    if(*query.record().begin()->begin()=="1"){
        return true;
    }else{
        return false;
    }
}

TEST_CASE( "Sqlite test", "select test" ) {

    REQUIRE( getContent() );
}


#endif // SQLITES_TEST_H
