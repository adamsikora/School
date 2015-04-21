%% Neural network

%% Initialization
clear ; close all; clc
%% Setup the parameters you will use for this exercise
input_layer_size  = 2;
hidden_layer_size = 2;
num_labels = 2;

%% Parameter initialization
%initial_Theta1 = randInitializeWeights(input_layer_size, hidden_layer_size);
%initial_Theta2 = randInitializeWeights(hidden_layer_size, num_labels);
initial_Theta1 = -1 + 2*rand(input_layer_size, hidden_layer_size + 1);
initial_Theta2 = -1 + 2*rand(hidden_layer_size, num_labels + 1);

% Unroll parameters
initial_nn_params = [initial_Theta1(:) ; initial_Theta2(:)];

X = [0 0; 0 1; 1 0; 1 1];
y = [1; 2; 2; 1];
m = size(X, 1);

%% Learning

%  value to see how more training helps.
options = optimset('MaxIter', 10000);

%  You should also try different values of lambda
lambda = 0;

[J, grad] = nnCostFunction(initial_nn_params, input_layer_size, hidden_layer_size, ...
                   num_labels, X, y, lambda);
% Create "short hand" for the cost function to be minimized
costFunction = @(p) nnCostFunction(p, ...
                                   input_layer_size, ...
                                   hidden_layer_size, ...
                                   num_labels, X, y, lambda);

% Now, costFunction is a function that takes in only one argument (the
% neural network parameters)
[nn_params, cost] = fmincg(costFunction, initial_nn_params, options);

% Obtain Theta1 and Theta2 back from nn_params
Theta1 = reshape(nn_params(1:hidden_layer_size * (input_layer_size + 1)), ...
                 hidden_layer_size, (input_layer_size + 1));

Theta2 = reshape(nn_params((1 + (hidden_layer_size * (input_layer_size + 1))):end), ...
                 num_labels, (hidden_layer_size + 1));

%Display data
%displayData(Theta1(:, 2:end));

% Prediction
pred = predict(Theta1, Theta2, X)
plot(cost);
fprintf('\nTraining Set Accuracy: %f\n', mean(double(pred == y)) * 100);
