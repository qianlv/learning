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
## @deftypefn {Function File} {@var{retval} =} dataset3Params (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author: qianlv <qianlv@qianlv-ThinkPad-T440p>
## Created: 2017-01-03

function [C, sigma] = dataset3Params (X, y, Xval, yval)
    C_vec = [0.01, 0.03, 0.1, 0.3, 1, 3, 10, 30];
    sigma_vec =[0.01, 0.03, 0.1, 0.3, 1, 3, 10, 30];
    C_len = numel(C_vec);
    sigma_len = numel(sigma_vec);
    minErr = 1;
    for n = 1:C_len,
        for m = 1:sigma_len,
            model = svmTrain(X, y, C_vec(n), @(x1, x2) gaussianKernel(x1, x2, sigma_vec(m))); 
            pred = svmPredict(model, Xval);
            err = mean(double(pred ~= yval));
            if err < minErr
                minErr = err;
                C = C_vec(n);
                sigma = sigma_vec(m);
            end
        end
    end
endfunction
