require "bundler/gem_tasks"
require "rake/extensiontask"
require "rake/testtask"

Rake::TestTask.new(:test) do |t|
  t.libs << "lib"
  t.pattern = "test/**/*_test.rb"
  t.verbose = true
end

Rake::ExtensionTask.new "similarity_sorting" do |ext|
  ext.lib_dir = "lib/similarity_sorting"
end

