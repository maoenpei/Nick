
use Cwd;

my $args = join(" ", @ARGV);
print "args: $args\n";

my $pwd = getcwd();
my $binary = "$pwd/Third/Binary";
my $cmake = "$binary/cmake/bin/cmake";
my $ninja = "$binary/ninja";
my $built = "$pwd/Built";

mkdir "$built";
mkdir "$built/Bin";
mkdir "$built/Int";
chdir "$built/Int";

my $VsEnv = "\"C:\\Program Files (x86)\\Microsoft Visual Studio 14.0\\VC\\vcvarsall.bat\"";

my $path = $ENV{"PATH"};
$ENV{"PATH"} = "$path;$binary";

my $arguments = "";
$arguments = "$arguments -DBUILT_DEPLOY=$built/Bin";

my $cmd = "$VsEnv x64 && $cmake $arguments -GNinja $pwd && $ninja Nick $args";
print "Building command - '$cmd'\n\n";
system($cmd);
