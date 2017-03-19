fprintf('Solving using library function fzero : ')

y = @(x) x - 0.5*sin(x) - 1;
value = fzero(y,10)
