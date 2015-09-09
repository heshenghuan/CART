# CART
classification and regression tree (CART) C++ implementation

Table of Contents
=================
- Introduction
- Data Format


Introduction
============
CART is a C++ implementation of classification and regression tree, which is 
a well-known algorithm for the DM (data mining). This is the soucecode of this
implementation.

Data Format
===========

The format of training and testing data file is:
<pre>
<label>	<index1>:<value1> <index2>:<value2> ...
.
.
.

Each line contains an instance and is ended by a '\n' character.

<label> is an float value indicating the class id in classification, or the
dependent variable value in regression. The range of class id should be from
1 to the size of classes. For example, the class id is 1, 2, 3 and 4 for a 
4-class classification problem. The range of dependent variable value shold 
be within the real number set.
 
<label> and <index>:<value> are sperated by a '\t' character. <index> is a postive
integer denoting the feature id. The range of feature id should be from 1 to the size
of feature set. For example, the feature id is 1, 2, ... 9 or 10 if the dimension of
feature set is 10. Indices must be in ASCENDING order. <value> is a float denoting the 
feature value. 

If the feature value equals 0, the <index>:<value> is encouraged to be neglected
for the consideration of storage space and computational speed.

Labels in the testing file are only used to calculate accuracy or errors. 
If they are unknown, just fill the first column with any class labels.
</pre>
