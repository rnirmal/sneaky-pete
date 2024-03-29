#ifndef __NOVA_GUEST_MYSQL_MYSQLPREPARER_H
#define __NOVA_GUEST_MYSQL_MYSQLPREPARER_H

#include "nova/guest/apt.h"
#include "nova/guest/mysql/MySqlAdmin.h"

namespace nova { namespace guest { namespace mysql {

/** A helper class to prepare the SQL database on an instance.
 *  Only the "prepare" method should be needed by other classes. */
class MySqlPreparer {
    public:

        MySqlPreparer(nova::guest::apt::AptGuest * apt);

        void create_admin_user(const std::string & password);

        /** Generate and set a random root password and forget about it. */
        void generate_root_password();

        /** Install the set of mysql my.cnf templates from dbaas-mycnf package.
         *  The package generates a template suited for the current
         *  container flavor. Update the os_admin user and password
         * to the my.cnf file for direct login from localhost
         **/
        void init_mycnf(const std::string & password);

        void install_mysql();

        // This is the only method that should be called by the SQL json stuff.
        void prepare();

        void remove_anonymous_user();

        void remove_remote_root_access();

        void restart_mysql();

    private:
        nova::guest::apt::AptGuest * apt;
        MySqlAdminPtr sql;
};

typedef boost::shared_ptr<MySqlPreparer> MySqlPreparerPtr;

} } }  // end nova::guest::mysql

#endif
