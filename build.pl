
use Cwd;

print @ARGV[0];

my $pwd = getcwd();
my $binary = "$pwd/Third/Binary";
my $cmake = "$binary/cmake/bin/cmake";
my $ninja = "$binary/ninja";

mkdir "Built";
chdir "./Built";

my $VsEnv = "\"C:\\Program Files (x86)\\Microsoft Visual Studio 14.0\\VC\\vcvarsall.bat\"";

my $path = $ENV{"PATH"};
$ENV{"PATH"} = "$path;$binary";

my $cmd = "$VsEnv x64 && $cmake -GNinja $pwd && $ninja";
print "Building command - '$cmd'\n\n";
system($cmd);
