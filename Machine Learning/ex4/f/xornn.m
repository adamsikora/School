%% Parameters
% XOR input for x1 and x2
input = [0 0; 0 1; 1 0; 1 1];
% Desired output of XOR
output = [0;1;1;0];
% Initialize the bias
bias = [-1 -1 -1];
% Learning coefficient
coeffbase = 0.1;
% Number of learning iterations
iterations = 500;
% Calculate weights randomly
initweights = -1 +2.*rand(3,3);
tries = 10;

%% Code
cost = zeros(iterations,tries);
for tr = 1:tries
    coeff = coeffbase*2^tr;
    weights = initweights;
for i = 1:iterations
   out = zeros(4,1);
   numIn = length (input(:,1));
   for j = 1:numIn
      % Hidden layer
      H1 = bias(1,1)*weights(1,1) + input(j,1)*weights(1,2) + input(j,2)*weights(1,3);

      % Send data through sigmoid function 1/1+e^-x
      x2(1) = sigmoid(H1);
      H2 = bias(1,2)*weights(2,1) + input(j,1)*weights(2,2) + input(j,2)*weights(2,3);
      x2(2) = sigmoid(H2);

      % Output layer
      x3_1 = bias(1,3)*weights(3,1) + x2(1)*weights(3,2) + x2(2)*weights(3,3);
      out(j) = sigmoid(x3_1);
      
      % Adjust delta values of weights
      % For output layer:
      % delta(wi) = xi*delta,
      % delta = (1-actual output)*(desired output - actual output) 
      delta3_1 = out(j)*(1-out(j))*(output(j)-out(j));
      
      % Propagate the delta backwards into hidden layers
      delta2_1 = x2(1)*(1-x2(1))*weights(3,2)*delta3_1;
      delta2_2 = x2(2)*(1-x2(2))*weights(3,3)*delta3_1;
      
      % Add weight changes to original weights 
      % And use the new weights to repeat process.
      % delta weight = coeff*x*delta
      for k = 1:3
         if k == 1 % Bias cases
            weights(1,k) = weights(1,k) + coeff*bias(1,1)*delta2_1;
            weights(2,k) = weights(2,k) + coeff*bias(1,2)*delta2_2;
            weights(3,k) = weights(3,k) + coeff*bias(1,3)*delta3_1;
         else % When k=2 or 3 input cases to neurons
            weights(1,k) = weights(1,k) + coeff*input(j,1)*delta2_1;
            weights(2,k) = weights(2,k) + coeff*input(j,2)*delta2_2;
            weights(3,k) = weights(3,k) + coeff*x2(k-1)*delta3_1;
         end
      end
   end
   cost(i, tr) = 1/numIn * sum((output-out).^2);
end
%fprintf('\nTraining: %f\n', tr);out
end
%plot(cost);

ColorSet = varycolor(tries);
set(gca, 'ColorOrder', ColorSet);

hold all;
for m = 1:tries
  plot(cost(:, m));
end

legend off
set(gcf, 'Colormap', ColorSet);
colorbar