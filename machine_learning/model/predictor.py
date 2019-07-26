"""
Define the predictor class for classifying according to help page.
"""

import cProfile
import time

# Third party imports
import numpy as np
from sklearn.base import BaseEstimator, ClassifierMixin

# Local imports
from common.keyword_vector import vector_distance, count_occurances, \
                                    read_dictionary
from common.lookuptable import create_table
from common.constants import KEYWORDS_FILE


class HelpPagePredictor(BaseEstimator, ClassifierMixin):
    """
    Classifier to assign the given input to a Singular helppage.
    """
    def __init__(self):
        """
        Define attributes
        """
        self.vectors = None
        self.files = None


    def fit(self, X, y): # pylint: disable=invalid-name
        """
        Setup the correspondence of vectors to help-files
        """
        assert X is not None, "Please provide data for X"
        assert y is not None, "Please provide data for y"
        self.vectors = X
        self.files = y
        return self


    def predict(self, X): # pylint: disable=invalid-name
        """
        Classify the input vectors
        """
        assert X is not None, "Please provide data for X"
        ret_list = []
        for x in X: # pylint: disable=invalid-name
            # find the closest vector

            min_val = float("inf")
            min_vec = None
            for vec in self.vectors:
                dist = vector_distance(x, vec)
                if dist < min_val:
                    min_val = dist
                    min_vec = vec

            # find corresponding filename
            index = list(self.vectors).index(min_vec)
            file = self.files[index]
            ret_list.append(file)
        return np.array(ret_list)


def main():
    """
    Run some basic tests
    """
    print("Running some tests")
    predictor = HelpPagePredictor()
    vector1 = {"hello":1, "bye":4, "pizza": 10}
    vector2 = {"hello":2, "bye":3, "pizza": 1}
    vector3 = {"hello":3, "bye":9, "pizza": 3}

    vectors = np.array([vector1, vector2, vector3])
    files = np.array(["file1", "file2", "file3"])
    print(vectors)
    print(files)

    testvec = {"hello":1, "bye":1, "pizza": 1}

    print("distance to 1")
    print(vector_distance(testvec, vector1))
    print()
    print("distance to 2")
    print(vector_distance(testvec, vector2))
    print()
    print("distance to 3")
    print(vector_distance(testvec, vector3))
    print()

    predictor.fit(vectors, files)
    prediction = predictor.predict(np.array([testvec]))
    print(prediction)

    dictionary = read_dictionary(KEYWORDS_FILE)
    start = time.time()
    vectors, file_list = create_table(dictionary=dictionary)
    end = time.time()
    print(end - start, "seconds to create_table")
    test_vec = count_occurances("extract.lib", dictionary)
    predictor.fit(vectors, file_list)
    start = time.time()
    prediction = predictor.predict(np.array([test_vec]))
    end = time.time()
    print(prediction)
    print(end - start, "seconds to make prediction")

if __name__ == '__main__':
    cProfile.run("main()")
