#include "nova/guest/utils.h"
#include <boost/format.hpp>
#include "nova/flags.h"
#include <iostream>
#include "nova/db/mysql.h"
#include "nova/guest/mysql/MySqlNovaUpdater.h"
#include <string>


using namespace nova::flags;
using boost::format;
using namespace nova::db::mysql;
using namespace nova::guest::mysql;
using std::string;
using namespace std;
namespace utils = nova::guest::utils;

struct nova::guest::mysql::MySqlNovaUpdaterTestsFixture {
    static void demo(int argc, char* argv[]) {
        FlagValues flags(FlagMap::create_from_args(argc, argv, true));

        MySqlConnectionPtr sql_connection(new MySqlConnection(
            flags.nova_sql_host(), flags.nova_sql_user(),
            flags.nova_sql_password()));

        cout << "Host Name = " << utils::get_host_name() << endl;

        string value = utils::get_ipv4_address(flags.guest_ethernet_device());
        cout << "Ip V4 Address = " << value << endl;

        MySqlNovaUpdater updater(sql_connection, flags.nova_sql_database(),
                                 flags.guest_ethernet_device());

        cout << "Instance ID = " << updater.get_guest_instance_id() << endl;

        cout << "Setting state to 'CRASHED'." << endl;

        updater.set_status(MySqlNovaUpdater::CRASHED);

        cout << "Current status of local db is "
             << updater.status_name(updater.get_actual_db_status()) << "."
             << endl;
    }

};

// Put this into a container to see if it can grab the correct information.
int main(int argc, char* argv[]) {
    nova::guest::mysql::MySqlNovaUpdaterTestsFixture::demo(argc, argv);
}
