import threading


# This is the function that each thread will execute.
def thread_sum(subarray, m_estimated, b_estimated, result):
    m_gradient = 0.0
    b_gradient = 0.0
    for point in subarray:
        y_predicted = m_estimated * point[0] + b_estimated
        b_gradient += point[1] - y_predicted
        m_gradient += point[0] * (point[1] - y_predicted)

    result.append((-2.0 * m_gradient, -2.0 * b_gradient))
    # Alternativa: return (-2.0 * m_gradient, -2.0 * b_gradient)


def thread_gradient_descent(num_data, learning_rate,
                            epochs, data_array):
    NUM_THREADS = 14
    print(f"\nStarting Thread Gradient Descent with {NUM_THREADS} threads")

    m_estimated = 0.0
    b_estimated = 0.0

    for epoch in range(epochs):
        m_gradient = 0.0
        b_gradient = 0.0

        threads = []
        results = []

        chunk_size = num_data // NUM_THREADS
        for i in range(NUM_THREADS):
            start = i * chunk_size
            end = start + chunk_size
            if i == NUM_THREADS - 1:
                end = num_data

            subarray = data_array[start:end]

            # Creando los hilos
            thread = threading.Thread(target=thread_sum,
                                      args=(subarray, m_estimated,
                                            b_estimated, results))
            threads.append(thread)
            thread.start()

        for thread in threads:
            thread.join()

        for res_mg, res_bg in results:
            m_gradient += res_mg
            b_gradient += res_bg

        m_gradient /= num_data
        b_gradient /= num_data

        m_estimated -= learning_rate * m_gradient
        b_estimated -= learning_rate * b_gradient

        if (epoch + 1) % (epochs // 2) == 0 or epoch == 0:
            # Error medio cuadratico
            # Meand Square Error
            mse = 0.0
            for i in range(num_data):
                y_predicted = m_estimated * data_array[i][0]\
                        + b_estimated
                mse += (data_array[i][1] - y_predicted) ** 2
            mse /= num_data
            print(f"Epoch {epoch + 1}/{epochs}: \
m_est = {m_estimated:.4f}, b_est \
= {b_estimated:.4f}, MSE = {mse:.4f}")

    return m_estimated, b_estimated
