
use Cwd;

print @ARGV[0];

my $pwd = getcwd();
my $cmake = "$pwd/cmake/bin/cmake";
my $ninja = "$pwd/ninja";

mkdir "Built";
chdir "./Built";

my $VsEnv = "\"C:\\Program Files (x86)\\Microsoft Visual Studio 14.0\\VC\\vcvarsall.bat\"";

system("$VsEnv x64 && $cmake -GNinja $pwd && $ninja");
