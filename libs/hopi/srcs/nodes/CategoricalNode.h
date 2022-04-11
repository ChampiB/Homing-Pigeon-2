//
// Created by Theophile Champion on 28/11/2020.
//

#ifndef HOMING_PIGEON_CATEGORICAL_NODE_H
#define HOMING_PIGEON_CATEGORICAL_NODE_H

#include "FactorNode.h"
#include "api/API.h"
#include <memory>
#include <torch/torch.h>

namespace hopi::nodes {
    class VarNode;
}

namespace hopi::nodes {

    /**
     * Class representing a factor node corresponding to an Categorical distribution.
     */
    class CategoricalNode : public FactorNode {
    public:
        //
        // Factories
        //

        /**
         * Create a Categorical factor node, i.e., representing the distribution P(to|d).
         * @param to the generated random variable
         * @param d the parameters of the distribution, i.e., a random vector distributed according to a Dirichlet
         * @return the created factor node
         */
        static std::unique_ptr<CategoricalNode> create(RV *to, RV *d);

        /**
         * Create a Categorical factor node, i.e., representing the distribution P(to).
         * @param to the generated random variable
         * @return the created factor node
         */
        static std::unique_ptr<CategoricalNode> create(RV *to);

    public:
        //
        // Constructors
        //

        /**
         * Construct a Categorical factor node, i.e., representing the distribution P(to|param).
         * @param to the generated random variable
         * @param param the parameters of the distribution, i.e., a random vector distributed according to a Dirichlet
         * @return the created factor node
         */
        CategoricalNode(VarNode *to, VarNode *param);

        /**
         * Create a Categorical factor node, i.e., representing the distribution P(to).
         * @param to the generated random variable
         * @return the created factor node
         */
        explicit CategoricalNode(VarNode *to);

        //
        // Implement the methods of the FactorNode class
        //

        /**
         * Getter.
         * @param i the index of the parent that must be returned
         * @return the i-the parent of the factor
         */
        VarNode *parent(int i) override;

        /**
         * Getter.
         * @return the child of the factor, i.e., the random variable generated by the factor.
         */
        VarNode *child() const override;

        /**
         * Compute the message towards a specific node
         * @param to the node toward which the message is sent
         * @return the message
         */
        torch::Tensor message(VarNode *to) override;

        /**
         * Compute the Variational Free Energy (VFE) of the factor
         * @return the VFE
         */
        double vfe() override;

    private:
        /**
         * Getter.
         * @return the message towards the generated random variable.
         */
        torch::Tensor childMessage();

        /**
         * Getter.
         * @return the message towards the random variable representing the parameters of the Categorical.
         */
        torch::Tensor dMessage();

        /**
         * Getter.
         * @return if the parameters are distributed according to a Dirichlet, then the expected logarithm of the
         * parameters, otherwise the logarithm of the parameters.
         */
        torch::Tensor getLogD();

    private:
        VarNode *childNode;
        VarNode *D;
    };

}

#endif //HOMING_PIGEON_CATEGORICAL_NODE_H
