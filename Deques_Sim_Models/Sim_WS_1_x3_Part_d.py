import random
import multiprocessing
import datetime

# define deque
class SimDeque:
    def __init__(self, de_number,
                 sk_size, sk_dist,
                 p_prob, q_prob, w_prob, pw_prob, qw_prob):
        self.num = de_number
        # deque sizes
        self.sk = sk_size
        self.dist = sk_dist
        # operation probabilities
        self.p = p_prob
        self.q = q_prob
        self.w = w_prob
        self.pw = pw_prob
        self.qw = qw_prob

# determine operation
def operat(p_prob, q_prob, w_prob, pw_prob, qw_prob):
    rnd = random.random()
    # operations
    push_prob = p_prob
    pop_prob = push_prob + q_prob
    steal_prob = pop_prob + w_prob
    push_steal_prob = steal_prob + pw_prob
    pop_steal_prob = push_steal_prob + qw_prob
    # output
    if 0 <= rnd < push_prob : return "push"
    elif push_prob <= rnd < pop_prob : return "pop"
    elif pop_prob <= rnd < steal_prob : return "steal"
    elif steal_prob <= rnd < push_steal_prob : return "push_steal"
    elif push_steal_prob <= rnd < pop_steal_prob : return "pop_steal"
    elif pop_steal_prob <= rnd < 1 : return "rest"
    else : print("operations error")

# define actions
def push_act(de_sim):
    global dist_1
    global end_sim
    de_sim.sk += 1
    if de_sim.num == 1 :
        dist_1 -= 1
        if dist_1 < 0 :
            end_sim = 1
            return
    else :
        de_sim.dist -= 1
        if de_sim.dist < 0 :
            end_sim = 1
            return
def pop_act(de_sim):
    global dist_1
    global end_sim
    de_sim.sk -= 1
    if de_sim.sk < 0 :
        end_sim = 1
        return
    if de_sim.num == 1 :
        dist_1 += 1
    else :
        de_sim.dist += 1
def steal_act():
    global dist_1
    global de_qe
    global end_sim
    de_qe -= 1
    if de_qe < 0 :
        end_sim = 1
        return
    dist_1 += 1

# define sub simulation
def pair_separate(de_sim, operat_sim):
    action = operat_sim
    # actions
    match action:
        case "push":
            push_act(de_sim)
        case "pop":
            pop_act(de_sim)
        case "steal":
            steal_act()
        case "push_steal":
            push_act(de_sim)
            steal_act()
        case "pop_steal":
            pop_act(de_sim)
            steal_act()
        case "rest":
            return
        case _:
            print ("actions error")

# define main simulation
def sim(s, d):
    # all simulations counters
    operat_avg_prev = 0
    operat_avg_curr = 0
    # all simulations process
    for iter_sim in range(10000000):
        # deque characteristics
        global m
        global de1_sk
        global de1_qe
        global de2_sk
        global de2_qe
        global de3_sk
        global de3_qe
        global de1_p
        global de1_q
        global de1_w
        global de1_pw
        global de1_qw
        global de2_p
        global de2_q
        global de2_w
        global de2_pw
        global de2_qw
        global de3_p
        global de3_q
        global de3_w
        global de3_pw
        global de3_qw
        global de_qe
        de1 = SimDeque(1,
                       de1_sk, None,
                       de1_p, de1_q, de1_w, de1_pw, de1_qw)
        de2 = SimDeque(2,
                       de2_sk, d-de2_sk,
                       de2_p, de2_q, de2_w, de2_pw, de2_qw)
        de3 = SimDeque(3,
                       de3_sk, m-s-d-de3_sk,
                       de3_p, de3_q, de3_w, de3_pw, de3_qw)
        de_qe = de1_qe + de2_qe + de3_qe
        # free sizes
        global dist_1
        dist_1 = s - ( de1.sk + de_qe )
        # single simulation counters
        global end_sim
        operat_num = 0
        end_sim = 0
        # single simulation process
        while end_sim == 0 :
            pair_separate(de1, operat(de1.p, de1.q, de1.w, de1.pw, de1.qw))
            pair_separate(de2, operat(de2.p, de2.q, de2.w, de2.pw, de2.qw))
            pair_separate(de3, operat(de3.p, de3.q, de3.w, de3.pw, de3.qw))
            operat_num += 1
        # single simulation results
        operat_avg_curr = operat_avg_prev + ( operat_num - operat_avg_prev ) / ( iter_sim + 1 )
        operat_avg_prev = operat_avg_curr
    # all simulations result
    print(str(multiprocessing.current_process()) + " value of s: " + str(s) + ", value of d: " + str(d) + ", average time: " + str(round(operat_avg_curr, 2)))


# input memory size
m = 100
# input deque sizes
de1_sk = 10
de1_qe = 10
de2_sk = 10
de2_qe = 10
de3_sk = 10
de3_qe = 10
# input operation probabilities
de1_p = 0.16
de1_q = 0.16
de1_w = 0.16
de1_pw = 0.16
de1_qw = 0.16
de2_p = 0.16
de2_q = 0.16
de2_w = 0.16
de2_pw = 0.16
de2_qw = 0.16
de3_p = 0.16
de3_q = 0.16
de3_w = 0.16
de3_pw = 0.16
de3_qw = 0.16
# determine s and d
s_and_d = []
s_start = de1_sk + de1_qe + de2_qe + de3_qe
s_end = m - ( de2_sk + de3_sk )
for s in range(s_start, s_end+1):
    d_start = de2_sk
    d_end = m - s - de3_sk
    for d in range(d_start, d_end+1):
        s_and_d.append([s,d])

def main():
    # output
    print("memory size: " + str(m))
    print("---------")
    print("deque 1 stack size: " + str(de1_sk))
    print("deque 1 queue size: " + str(de1_qe))
    print("---")
    print("deque 2 stack size: " + str(de2_sk))
    print("deque 2 queue size: " + str(de2_qe))
    print("---")
    print("deque 3 stack size: " + str(de3_sk))
    print("deque 3 queue size: " + str(de3_qe))
    print("---------")
    print("deque 1 push probability: " + str(de1_p))
    print("deque 1 pop probability: " + str(de1_q))
    print("deque 1 steal probability: " + str(de1_w))
    print("deque 1 push and steal probability: " + str(de1_pw))
    print("deque 1 pop and steal probability: " + str(de1_qw))
    print("---")
    print("deque 2 push probability: " + str(de2_p))
    print("deque 2 pop probability: " + str(de2_q))
    print("deque 2 steal probability: " + str(de2_w))
    print("deque 2 push and steal probability: " + str(de2_pw))
    print("deque 2 pop and steal probability: " + str(de2_qw))
    print("---")
    print("deque 3 push probability: " + str(de3_p))
    print("deque 3 pop probability: " + str(de3_q))
    print("deque 3 steal probability: " + str(de3_w))
    print("deque 3 push and steal probability: " + str(de3_pw))
    print("deque 3 pop and steal probability: " + str(de3_qw))
    print("---------")
    # pool of processes
    sim_parallel = multiprocessing.Pool()
    # simulation in parallel
    print("simulation start: " + str(datetime.datetime.now()))
    print("---")
    sim_parallel.starmap(sim, s_and_d)
    print("---")
    print("simulation end: " + str(datetime.datetime.now()))

if __name__ == "__main__":
    main()
