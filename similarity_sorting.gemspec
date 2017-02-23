# coding: utf-8
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'similarity_sorting/version'

Gem::Specification.new do |spec|
  spec.name          = "similarity_sorting"
  spec.version       = SimilaritySorting::VERSION
  spec.authors       = ["Benjamin Vetter"]
  spec.email         = ["vetter@flakks.com"]
  spec.description   = %q{Ruby C extension to speed up similarity sorting}
  spec.summary       = %q{Ruby C extension to speed up similarity sorting}
  spec.homepage      = "https://github.com/mrkamel/similarity_sorting"
  spec.license       = "MIT"

  spec.extensions    = %w[ext/similarity_sorting/extconf.rb]
  spec.files         = `git ls-files`.split($/)
  spec.executables   = spec.files.grep(%r{^bin/}) { |f| File.basename(f) }
  spec.test_files    = spec.files.grep(%r{^(test|spec|features)/})
  spec.require_paths = ["lib"]

  spec.add_development_dependency "bundler"
  spec.add_development_dependency "rake"
  spec.add_development_dependency "minitest"
end

