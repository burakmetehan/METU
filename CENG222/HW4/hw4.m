N = 4145; % size of Monte Carlo Simulation
total_weight = zeros(N,1); % vector to keep the total weight of vehicles for each monte carlo run

for k=1:N
    weight = 0; % the total weight for this monte carlo run

    % automobiles
    lambda = 50;      % parameter
    U = rand;         % generated uniform variable
    i = 0;            % initial value
    F = exp(-lambda); % initial value of F(0)
    while (U>=F)
        i = i + 1;
        F = F + exp(-lambda) * lambda^i / gamma(i+1);
    end

    n_a = i;        % total number of automobiles
    for j=1:n_a     % summing total weight of automobiles
        X = sum(-1/0.15 * log(rand(190,1))); % formula from example 5.11
        weight = weight + X;
    end

    % trucks
    lambda = 10;      % parameter
    U = rand;         % generated uniform variable
    i = 0;            % initial value
    F = exp(-lambda); % initial value of F(0)
    while (U>=F)
        i = i + 1;
        F = F + exp(-lambda) * lambda^i / gamma(i+1);
    end

    n_t = i;        % total number of trucks
    for j=1:n_t     % summing total weight of trucks
        X = sum(-1/0.01 * log(rand(110,1))); % formula from example 5.11
        weight = weight + X;
    end

    total_weight(k) = weight;
end

prob_over_200 = mean(total_weight > 200000);
expected_total_weight = mean(total_weight);
std_weight = std(total_weight);

fprintf('Estimated probability = %f\n', prob_over_200);
fprintf('Expected weight = %f\n', expected_total_weight);
fprintf('Standard deviation = %f\n', std_weight);
