
use Getopt::Long 'GetOptions';
use File::Path 'make_path';
use Cwd;

# arguments
my $variant;
my $verbose;

GetOptions(
    'variant|var=s' => \$variant,
    'verbose|v!' => \$verbose,
);

my $args = join(" ", @ARGV);
print "args: $args\n";

# setup paths
my $pwd = getcwd();
my $third_binary_path = "$pwd/Third/Binary";
my $built_path = "$pwd/Built";
my $cmake = "$third_binary_path/cmake/bin/cmake";
my $ninja = "$third_binary_path/ninja";

my $deploy_path = "$built_path/Bin";
my $internal_path = "$built_path/Int";
make_path "$deploy_path";
make_path "$internal_path";

# make sure 'ninja' is visitable
my $path = $ENV{"PATH"};
$ENV{"PATH"} = "$path;$third_binary_path";

if (not $variant) {
    $variant = "ninja";
}

# common variables
my $VsEnvScript = "\"C:\\Program Files (x86)\\Microsoft Visual Studio 14.0\\VC\\vcvarsall.bat\"";

# setup build environment
my $building_type = "Debug";
my %cmake_args = ();
my $cmake_gen;
my $pre_cmd;
my $post_cmd;

my $varName;
if ($variant eq "vs") {
    BuildVsProject();
} elsif ($variant eq "ninja") {
    BuildNinjaProject();
}

sub BuildVsProject{
    $varName = "vs_win32";
    $cmake_gen = "Visual Studio 14 2015 Win64";
    $post_cmd = "$VsEnvScript x64 && devenv Nick.sln /Build";
    $cmake_args{CMAKE_CONFIGURATION_TYPES} = $building_type;
}

sub BuildNinjaProject{
    $varName = "ninja_win32";
    $cmake_gen = "Ninja";
    $pre_cmd = "$VsEnvScript x64";
    $post_cmd = "$ninja Nick $args";
    if ($verbose) {
        $post_cmd = "$post_cmd -v";
    }
    $cmake_args{CMAKE_BUILD_TYPE} = $building_type;
}

$varName or die "Not valid variant!";

# ready to build
my $varDir = "${varName}_${building_type}";
$cmake_args{PROJ_DEPLOY} = "$deploy_path/$varDir";
$cmake_args{PROJ_BUILD_TYPE} = "$building_type";
make_path "$internal_path/$varDir";
chdir "$internal_path/$varDir";
print "In working directory: $internal_path/$varDir\n";

# setup cmake command
my $cmake_args_str = "";
while (my ($key, $val) = each %cmake_args) {
    $cmake_args_str = "$cmake_args_str -D$key=$val";
}
$cmake_cmd = "$cmake $cmake_args_str";
if ($cmake_gen) {
    $cmake_cmd = "$cmake_cmd -G \"$cmake_gen\"";
}
$cmake_cmd = "$cmake_cmd $pwd";

# start to build
print "Building command - '$building_cmd'\n\n";
open(EXECUTOR, "| cmd.exe /K \"echo off\" |");
if ($pre_cmd) {
    print EXECUTOR "$pre_cmd\n";
}
print EXECUTOR "$cmake_cmd\n";
if ($post_cmd) {
    print EXECUTOR "$post_cmd\n";
}
close(EXECUTOR);
