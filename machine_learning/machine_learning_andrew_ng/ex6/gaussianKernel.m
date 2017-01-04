## Copyright (C) 2017 qianlv
## 
## This program is free software; you can redistribute it and/or modify it
## under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 3 of the License, or
## (at your option) any later version.
## 
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
## 
## You should have received a copy of the GNU General Public License
## along with this program.  If not, see <http://www.gnu.org/licenses/>.

## -*- texinfo -*- 
## @deftypefn {Function File} {@var{retval} =} gaussianKernel (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author: qianlv <qianlv@qianlv-ThinkPad-T440p>
## Created: 2017-01-03

function [sim] = gaussianKernel (x1, x2, sigma)
    sim = exp(-(x1 - x2) * (x1 - x2)' / (2 * sigma * sigma));
endfunction
