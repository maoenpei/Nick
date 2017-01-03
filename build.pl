
use Cwd;

my $pwd = getcwd();
my $cmake = "$pwd/cmake/bin/cmake";

chdir "./Built";

system("$cmake $pwd");
