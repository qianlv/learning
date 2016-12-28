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
## @deftypefn {Function File} {@var{retval} =} featureNormalize (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author: qianlv <qianlv@qianlv-ThinkPad-T440p>
## Created: 2016-12-27


function [X_norm, mu, sigma] = featureNormalize (X) 
    X_norm = X;
    sigma = zeros(1, size(X, 2))
    mu = zeros(1, size(X, 2))
    mu = mean(X);
    sigma = std(X);

    m = size(X, 1);
    for i = 1 : m,
        X_norm(i, :) = X(i, :) - mu;
    end

    for i = 1 : m,
        X_norm(i, :) = X_norm(i, :) ./ sigma;
    end
endfunction
