##################################################################################################
#
# gv_shell_spec.rb
#
# Author::    Zachary Kurmas
# Copyright:: (c) Zachary Kurmas 2026
#
##################################################################################################
require 'spec_helper'

describe 'GVSpec' do

    it 'runs a single one-token command' do
        result = run_gv_shell('ls')
        expect(result[:exit]).to equal 0

        expect(result[:out]).to include('gv_shell')
        expect(result[:out]).to include('spec')
        expect(result[:out]).to match(/Process \d+ terminated with exit status 0/)
    end

    it 'runs a single two-token command' do
        result = run_gv_shell('ls -la')
        expect(result[:exit]).to equal 0

        expect(result[:out]).to include('gv_shell')
        expect(result[:out]).to include('spec')
        expect(result[:out]).to include('..')
        expect(result[:out]).to include('total')
        expect(result[:out]).to match(/Process \d+ terminated with exit status 0/)
    end

    it 'pipes two commands' do
        result = run_gv_shell("echo 'That was the year that was' | wc")
        expect(result[:exit]).to eq 0

        expect(result[:out]).to match(/1\s+6\s+27/)
        expect(result[:out]).to match(/Process \d+ terminated with exit status 0/)
    end

    it 'detects multiple redirects' do
        result = run_gv_shell("ls > a > b")
        expect(result[:exit]).to be_nonzero
    end
end