##################################################################################################
#
# spec_helper.rb
#
# Author::    Zachary Kurmas
# Copyright:: (c) Zachary Kurmas 2017
#
##################################################################################################

require 'external_runner'
require 'env_helper'

RSpec.configure do |config|

end

def run_gv_shell(*args) 

  # Since we group arguments with double-quotes, then we can't have 
  # double quotes in the args
  message = "TEST FORMAT ERROR: Arguments used for tests may not contain double quotes."
  fail message if args.any? { |s| s.include?('"') }

  command = "./gv_shell " + args.map { |a| %("#{a}") }.join(' ')

  puts "Running command =>#{command}<=" if EnvHelper.debug_mode?
  result = ExternalRunner.run(command)
  if EnvHelper.debug_mode?
    puts result[:out]
    puts result[:err]
  end
  result
end


######################################################
#
# Constants used by specs
#
# (They are gathered here in one place so they are
#  easier to find and update.)
#
#####################################################
module Constants

end

module ExitValues

  ALL_TESTS_PASS = 0
  INFO_ONLY = 2
  SOME_TEST_FAILED = 3
  INVALID_PARAMETER = 4
  INVALID_CIRCUIT = 8
  INVALID_TEST_CLASS = 12
  SETUP_FAILED = 13

end


################################################################################
#
# Misc. helper methods.
#
###############################################################################

#
# add indentation to the beginning of the string.  The method infers the desired
# amount of indentation from the content of the string.
#
# We use this helper method so that it is easy to update the tests should we
# ever decide to change the amount by which things are indented.
#

def indent(string)

  string.strip!

  if string =~ /^Failure/
    Constants::FAILURE_INDENT + string
  elsif string =~ /^Test Error:/ || string =~ /^\(In this circuit/
    Constants::FAILURE_INDENT + string
  elsif string =~ /^\(We guess/
    Constants::FAILURE_INDENT + '   ' + string
  elsif string =~/^Tests run:/ || string =~/^Circuits containing/
    string
  else
    abort "Problem with spec code:  String =>#{string}<= is not of a format that is expected to be indented."
  end
end

################################################################################
#
# Matchers
#
###############################################################################

#
# Verifies that array contains at least one matching line
#
RSpec::Matchers.define :include_line_matching do |expected|
  match do |actual|
    actual.find { |line| line =~ expected }
  end

  failure_message do |actual|
    "expected #{actual} to include a line matching #{expected}"
  end
end