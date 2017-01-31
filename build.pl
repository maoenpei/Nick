
use Cwd;

print @ARGV[0];

my $pwd = getcwd();
my $cmake = "$pwd/cmake/bin/cmake";
my $ninja = "$pwd/ninja";

mkdir "Built";
chdir "./Built";

my $VsEnv = "\"C:\\Program Files (x86)\\Microsoft Visual Studio 14.0\\VC\\vcvarsall.bat\"";

my $path = $ENV{"PATH"};
$ENV{"PATH"} = "$path;$pwd";

my $cmd = "$VsEnv x64 && $cmake -GNinja $pwd && $ninja";
print "Building command - '$cmd'\n\n";
system($cmd);
