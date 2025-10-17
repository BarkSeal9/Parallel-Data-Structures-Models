import random

# define deque
class SimDeque:
    def __init__(self, de_number,
                 sk_size,
                 p_prob, q_prob, w_prob, pw_prob, qw_prob):
        self.num = de_number
        # deque sizes
        self.sk = sk_size
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
    global dist_2
    global end_sim
    de_sim.sk += 1
    if de_sim.num == 1 :
        dist_1 -= 1
        if dist_1 < 0 :
            end_sim = 1
            return
    else :
        dist_2 -= 1
        if dist_2 < 0 :
            end_sim = 1
            return
def pop_act(de_sim):
    global dist_1
    global dist_2
    global end_sim
    de_sim.sk -= 1
    if de_sim.sk < 0 :
        end_sim = 1
        return
    if de_sim.num == 1 :
        dist_1 += 1
    else :
        dist_2 += 1
def steal_act():
    global dist_1
    global dist_2
    global de_qe
    global end_sim
    de_qe -= 1
    if de_qe < 0 :
        end_sim = 1
        return
    dist_1 += 1

# define simulation
def pair_facing(de_sim, operat_sim):
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
de1_p = float(input("deque 1 push probability: "))
de1_q = float(input("deque 1 pop probability: "))
de1_w = float(input("deque 1 steal probability: "))
de1_pw = float(input("deque 1 push and steal probability: "))
de1_qw = float(input("deque 1 pop and steal probability: "))
de2_p = float(input("deque 2 push probability: "))
de2_q = float(input("deque 2 pop probability: "))
de2_w = float(input("deque 2 steal probability: "))
de2_pw = float(input("deque 2 push and steal probability: "))
de2_qw = float(input("deque 2 pop and steal probability: "))
de3_p = float(input("deque 3 push probability: "))
de3_q = float(input("deque 3 pop probability: "))
de3_w = float(input("deque 3 steal probability: "))
de3_pw = float(input("deque 3 push and steal probability: "))
de3_qw = float(input("deque 3 pop and steal probability: "))
# determine starting s
s = de1_sk + de1_qe + de2_qe + de3_qe

# s simulation process
while s <= m - ( de2_sk + de3_sk ) :
    # all simulations counters
    operat_avg_prev = 0
    operat_avg_curr = 0
    # all simulations process
    for iter_sim in range(10000000):
        # deque characteristics
        de1 = SimDeque(1,
                       de1_sk,
                       de1_p, de1_q, de1_w, de1_pw, de1_qw)
        de2 = SimDeque(2,
                       de2_sk,
                       de2_p, de2_q, de2_w, de2_pw, de2_qw)
        de3 = SimDeque(3,
                       de3_sk,
                       de3_p, de3_q, de3_w, de3_pw, de3_qw)
        de_qe = de1_qe + de2_qe + de3_qe
        # free sizes
        dist_1 = s - ( de1.sk + de_qe )
        dist_2 = m - s - ( de2.sk + de3.sk )
        # single simulation counters
        operat_num = 0
        end_sim = 0
        # single simulation process
        while end_sim == 0 :
            pair_facing(de1, operat(de1.p, de1.q, de1.w, de1.pw, de1.qw))
            pair_facing(de2, operat(de2.p, de2.q, de2.w, de2.pw, de2.qw))
            pair_facing(de3, operat(de3.p, de3.q, de3.w, de3.pw, de3.qw))
            operat_num += 1
        # single simulation results
        operat_avg_curr = operat_avg_prev + ( operat_num - operat_avg_prev ) / ( iter_sim + 1 )
        operat_avg_prev = operat_avg_curr
    # all simulations result
    print("value of s: " + str(s))
    print("average time: " + str(round(operat_avg_curr, 2)))
    s += 1
