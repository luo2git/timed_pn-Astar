# coding: utf-8

import os
os.environ["CUDA_DEVICE_ORDER"] = "PCI_BUS_ID"
os.environ["CUDA_VISIBLE_DEVICES"] = "-1"
import tensorflow as tf
import pandas as pd

class_label = {'000011':0, '100001':1, '010001':2, '001010':3, '000110':4, '101000':5,
       '011000':6, '100100':7, '010100':8}

def data_process(path):
    data = pd.read_table(path, header=None)
    data_pro = pd.DataFrame()
    data_pro["M0"] = data.iloc[:, 1].apply(lambda x: int(x[1]))
    data_pro["M1"] = data.iloc[:, 1].apply(lambda x: int(x[3]))
    data_pro["M4"] = data.iloc[:, 1].apply(lambda x: int(x.replace(" ", "")[4]))
    data_pro["M5"] = data.iloc[:, 1].apply(lambda x: int(x.replace(" ", "")[5]))
    data_pro["M8"] = data.iloc[:, 1].apply(lambda x: int(x.replace(" ", "")[8]))
    data_pro["M9"] = data.iloc[:, 1].apply(lambda x: int(x.replace(" ", "")[9]))
    data_pro["M_class"] = data.iloc[:, 1].apply(lambda x: x.replace(" ", ""))
    data_pro["M_class"] = data_pro["M_class"].apply(lambda x: "".join([x[i] for i in [2, 3, 6, 7, 10, 11]]))
    data_pro["M_class"] = data_pro["M_class"].replace(class_label)
    data_pro["X_2"] = data.iloc[:, 2].apply(lambda x: int(x.replace(" ", "")[2]))
    data_pro["X_3"] = data.iloc[:, 2].apply(lambda x: int(x.replace(" ", "")[3]))
    data_pro["X_6"] = data.iloc[:, 2].apply(lambda x: int(x.replace(" ", "")[6]))
    data_pro["X_7"] = data.iloc[:, 2].apply(lambda x: int(x.replace(" ", "")[7]))
    data_pro["g"] = data.iloc[:, 3]
    return data_pro


def predict(X,keep_prob=1):

    print("进入模型")
    with tf.Session() as sess:

        # restore saver
        saver = tf.train.import_meta_graph(meta_graph_or_file="H:/TimedPN_A_Predict/nn_boston_model/nn_boston.model-100000.meta")
        model_file = tf.train.latest_checkpoint(checkpoint_dir="H:/TimedPN_A_Predict/nn_boston_model")
        saver.restore(sess=sess,save_path=model_file)

        # init graph
        graph = tf.get_default_graph()

        # get placeholder from graph
        xs = graph.get_tensor_by_name("inputs:0")
        # ys = graph.get_tensor_by_name("y_true:0")
        # keep_prob_s = graph.get_tensor_by_name("keep_prob:0")

        # get operation from graph
        pred = graph.get_tensor_by_name("pred:0")

        # run pred
        feed_dict = {xs: X}
        y_pred = sess.run(pred,feed_dict=feed_dict)

    return y_pred.reshape(-1)

def Astar_Predict(path):

    a = data_process(path)
    y_pred = max(float(predict(X= a.iloc[-1].values.reshape(1,-1), keep_prob=1)), 0.)
    # print(y_pred)
    return y_pred

# Astar_Predict("J:\\原--数据\\桌面\\timed-PN\\timedPN\\timedPN\\data_process\\backout2.txt")