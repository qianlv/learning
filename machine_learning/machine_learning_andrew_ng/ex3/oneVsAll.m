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
## @deftypefn {Function File} {@var{retval} =} oneVsAll (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author: qianlv <qianlv@qianlv-ThinkPad-T440p>
## Created: 2016-12-30

function [all_theta] = oneVsAll (X, y, num_labels, lambda)
    n = size(X, 2);
    m = size(X, 1);
    X = [ones(m, 1) X];
    all_theta = zeros(num_labels, n + 1);
    for i = 1:num_labels,
        init_theta = zeros(n + 1, 1);
        options = optimset('GradObj', 'on', 'MaxIter', 50);
        [theta, cost] = fmincg(@(t)lrCostrFunction(t, X, (y == i), lambda), init_theta, options);
        % [theta, cost] = fminunc(@(t)lrCostrFunction(t, X, (y == i), lambda), init_theta, options);

        all_theta(i, :) = theta';
    end
endfunction
