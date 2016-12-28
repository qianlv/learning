## Copyright (C) 2016 qianlv
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
## @deftypefn {Function File} {@var{retval} =} gradientDescentMulti (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author: qianlv <qianlv@qianlv-ThinkPad-T440p>
## Created: 2016-12-28

function [theta, J_history] = gradientDescentMulti (X, y, theta, alpha, num_iters)
    m = size(X, 1);
    n = size(X, 2);
    J_history = zeros(num_iters, 1);
    for iter = 1 : num_iters
        T = X * theta - y;
        theta = theta - (alpha * X' * T) / m;
        J_history(iter) = computeCost(X, y, theta);
    end
endfunction
