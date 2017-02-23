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
## @deftypefn {Function File} {@var{retval} =} cofiCostFunc (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author: qianlv <qianlv@qianlv-ThinkPad-T440p>
## Created: 2017-01-06

function [J, grad] = cofiCostFunc (params, Y, R, num_users, num_movies, num_features, lambda)
    X = reshape(params(1:num_movies * num_features), num_movies, num_features);
    theta = reshape(params(num_movies * num_features + 1:end), num_users, num_features);
    H = X * theta';
    J = 0.5 * sum(sum((R .* (H - Y)) .^ 2)) + lambda / 2 * (sum(sum(theta .^ 2)) + sum(sum(X .^ 2)));

    X_grad = R .* (H - Y) * theta + lambda * X;
    Theta_grad = (R .* (H - Y))' * X + lambda * theta;

    grad = [X_grad(:); Theta_grad(:)];
endfunction
