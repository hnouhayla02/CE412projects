import simpy #facilates time scheduling and progess
import random
import matplotlib.pyplot as plt

#let's break the tast into small tasks:
#based on instruction...
# -The production line is divided into several phases:
# raw material handling, machining, assembly, quality control, and packaging.
# Each stage includes specific machinery and labor requirements, operating across multiple shifts.
#so functions needed : machining(), assembly(), quality_control() and package()
#maybe also visualize these steps




RANDOM_SEED =50
RAW_MATERIAL_INTERVAL=5
MACHINING_TIME= 10
ASSEMBLY_TIME =10
QUALITY_CONTROL_TIME =15
PACKAGING_TIME = 5
SIMU_TIME =50 #JUST TO TEST FIRST *ADD LATER*

LOADING_TIME = 3
INSPECTION_TIME=3


#GET RANDOM
random.seed(RANDOM_SEED)


events = []


def log_event(event_type, time, task_name)
    events.append((event_type, time, task_name))


def raw_material_generator(env, raw_material_queue)
    while True:
        yield env.timeout(RAW_MATERIAL_INTERVAL)
        raw_material_queue.put(env.now)
        log_event('start', env.now, 'Raw Material')
        print(f"Raw material added at {env.now} minute")



#loading based on each task
def loading(env, task_name):
    log_event('start', env.now, task_name)
    print(f"{task_name} started at {env.now} minutes")
    yield env.timeout(LOADING_TIME)
    log_event("finish", env.now, task_name)
    print(f"{task_name} finished at {env.now} minutes")



def machining(env, raw_material_queue, machining_queue):
    while True:
        #starting time
        yield raw_material_queue.get()
        log_event('start', env.now, 'Machining')
        print(f"Machining will start at {env.now} minutes")
        #finishing time
        yield env.timeout(MACHINING_TIME)
        machining_queue.put(env.now)
        log_event('finish', env.now, 'Machining')
        print(f"Machining finished at {env.now} minutes")


def assembly(env, machining_queue, assembly_queue):
    while True:
        yield machining_queue.get()
        log_event('start', env.now, 'Assembly')
        print(f"Assembly started at {env.now} minutes")
        yield env.timeout(ASSEMBLY_TIME)
        assembly_queue.put(env.now)
        log_event('finish', env.now, 'Assembly')
        print(f"Assembly finished at {env.now} minutes")


def quality_control(env, assembly_queue, qc_queue):
    while True:
        yield assembly_queue.get()
        log_event('start', env.now, 'Quality Control')
        print(f"Quality control start is at {env.now} minutes")
        yield env.timeout(QUALITY_CONTROL_TIME)
        qc_queue.put(env.now)
        log_event('finish', env.now, 'Quality Control')
        print(f"Quality control finished at {env.now} minutes")


def package(env, qc_queue, packaging_queue):
    while True:
        yield qc_queue.get()
        log_event('start', env.now, 'Packaging')
        print(f"Packaging start is at {env.now} minutes")
        yield env.timeout(PACKAGING_TIME)
        packaging_queue.put(env.now)
        log_event('finish', env.now, 'Packaging')
        print(f"Packaging finished at {env.now} minutes")
        print(f"Packaging finished at {env.now} minutes")


#the main simulation function
def run_simulation():
    env = simpy.Environment()

    raw_material_queue = simpy.Store(env)
    machining_queue = simpy.Store(env)
    assembly_queue = simpy.Store(env)
    qc_queue = simpy.Store(env)
    packaging_queue = simpy.Store(env)

    env.process(raw_material_generator(env, raw_material_queue))
    env.process(machining(env, raw_material_queue, machining_queue))
    env.process(assembly(env, machining_queue, assembly_queue))
    env.process(quality_control(env, assembly_queue, qc_queue))
    env.process(package(env, qc_queue, packaging_queue))

    env.run(until=SIMU_TIME)

    #then visualizing every thing using a gantt chart
    visualize_events()


#the visualizer function (not sure it works) *FIX IT LATERR*
def visualize_events():
    tasks = {}
    for event_type, time, task_name in events:
        if task_name not in tasks:
            tasks[task_name] = {'start': [], 'finish': []}
        tasks[task_name][event_type].append(time)

    fig, ax = plt.subplots(figsize=(10, 6))
    y_labels = []
    for i, (task_name, times) in enumerate(tasks.items()):
        y_labels.append(task_name)
        for start, finish in zip(times['start'], times['finish']):
            ax.broken_barh([(start, finish - start)], (i - 0.4, 0.8), facecolors='tab:green')

    ax.set_yticks(range(len(y_labels)))
    ax.set_yticklabels(y_labels)
    ax.set_xlabel('Time (minutes)')
    ax.set_ylabel('Tasks')
    ax.set_title('Manufacturing Line Simulation Gantt Chart')
    plt.show()


if __name__ == "__main__":
    run_simulation()