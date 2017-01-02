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
## @deftypefn {Function File} {@var{retval} =} validationCurve (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author: qianlv <qianlv@qianlv-ThinkPad-T440p>
## Created: 2017-01-02

function [lambda_vec, error_train, error_val] = validationCurve (X_poly, y, X_poly_val, yval)
    lambda_vec = [0, 0.001, 0.003, 0.01, 0.03, 0.1, 0.3, 1, 3, 10];
    lv_len = numel(lambda_vec);
    error_train = zeros(lv_len, 1);
    error_val = zeros(lv_len, 1);
    for i = 1:numel(lambda_vec),
        lambda = lambda_vec(i);
        theta = trainLinearReg(X_poly, y, lambda);
        error_train(i) = linearRegCostFunction(X_poly, y, theta, 0);
        error_val(i) = linearRegCostFunction(X_poly_val, yval, theta, 0); 
    end
endfunction
