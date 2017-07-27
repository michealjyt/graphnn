#ifndef CPU_ROW_SPARSE_TENSOR_H
#define CPU_ROW_SPARSE_TENSOR_H

#include "tensor.h"
#include "cpu_dense_tensor.h"
#include "t_data.h"

namespace gnn
{

/**
 * @brief      CPU ROW_SPARSE specialization of Tensor
 *
 * @tparam     Dtype  { float/double }
 */
template<typename Dtype>
class TensorTemplate<CPU, ROW_SPARSE, Dtype> : public Tensor
{
public:

	TensorTemplate();
	virtual ~TensorTemplate() {}
	virtual void Reshape(std::vector<size_t> l) override;
	virtual MatType GetMatType() override;
	virtual MatMode GetMatMode() override;

	/**
	 * @brief      return a view from dense tensor
	 *
	 * @return     dense referenced tensor
	 */
	DTensor<CPU, Dtype> Full();
	/**
	 * @brief      set this tensor to be zero
	 */
	void SparseZeros();
	/**
	 * @brief      set this full tensor to be zero
	 */
	void FullZeros();

	/**
	 * @brief      fill this tensor with same scalar
	 *
	 * @param[in]  scalar  The scalar to be set
	 */
	void Fill(Dtype scalar);

	/**
	 * @brief      compute and store the result (a dense matrix) of matrix multiplication; 
	 *				this = alpha * A x B + beta * this
	 * @param      a       operand A (dense matrix)
	 * @param      b       operand B (dense matrix)
	 * @param[in]  transA  whether to transpose A
	 * @param[in]  transB  whether to transpose B
	 * @param[in]  alpha   The alpha
	 * @param[in]  beta    The beta
	 */
	void MM(DTensor<CPU, Dtype>& a, DTensor<CPU, Dtype>& b, Trans transA, Trans transB, Dtype alpha, Dtype beta);

	/**
	 * @brief      compute and store the result (a dense matrix) of matrix multiplication; 
	 *				this = alpha * A x B + beta * this
	 * @param      a       operand A (sparse matrix)
	 * @param      b       operand B (dense matrix)
	 * @param[in]  transA  whether to transpose A
	 * @param[in]  transB  whether to transpose B
	 * @param[in]  alpha   The alpha
	 * @param[in]  beta    The beta
	 */
	void MM(SpTensor<CPU, Dtype>& a, DTensor<CPU, Dtype>& b, Trans transA, Trans transB, Dtype alpha, Dtype beta);

	/**
	 * @brief      the same axpy defined in blas: y = a * x + y
	 *
	 * @param[in]  a     scalar a
	 * @param      x     dense tensor x
	 */
	void Axpy(Dtype a, DTensor<CPU, Dtype>& x);
	
	/**
	 * @brief      the same axpby defined in blas: y = a * x + b * y
	 *
	 * @param[in]  a     scalar a
	 * @param      x     dense tensor x
	 * @param[in]  b     scalar b
	 */
	void Axpby(Dtype a, DTensor<CPU, Dtype>& x, Dtype b);

	/**
	 * @brief      get l2-norm of tensor
	 *
	 * @return     norm2 scalar
	 */
	Dtype Norm2();

	/**
	 * @brief      set each element x to be x^2
	 */
	void Square();

	/**
	 * the shared ptr to the data structure (which is used to keep the data of this tensor)
	 */
	std::shared_ptr< DenseData<CPU, Dtype> > data;

	/**
	 * rows that have values
	 */
	DTensor<CPU, int> row_idxes;

	/**
	 * is dense matrix?
	 */
	bool is_full;
};

/**
 * @brief      CPU ROW_SPARSE int tensor specialization; this tensor is not used for heavy computation
 */
template<>
class TensorTemplate<CPU, ROW_SPARSE, int> : public Tensor
{
public:

	TensorTemplate();
	virtual ~TensorTemplate() {}
	virtual void Reshape(std::vector<size_t> l) override;
	virtual MatType GetMatType() override;
	virtual MatMode GetMatMode() override;
	/**
	 * @brief      set this tensor to be zero
	 */
	void SparseZeros() {}
	/**
	 * @brief      set this full tensor to be zero
	 */
	void FullZeros() {}
	/**
	 * @brief      fill this tensor with same scalar
	 *
	 * @param[in]  scalar  The scalar to be set
	 */
	void Fill(int scalar) {}
};

}

#endif